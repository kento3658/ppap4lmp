/* ---------------------------------------------------------------------
ProData: stands for Processor which returns Data itself.

create: 2018/06/22 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "pro_data.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

void ProData::select(pybind11::args args)
{
  for (const auto &a : args)
  {
    selected_keys.push_back(a.cast<std::string>());
  }
}

/* ------------------------------------------------------------------ */

void ProData::run_impl(int i_generator)
{
  auto &d = generators[i_generator]->get_data();

  if (selected_keys.size() == 0)
  {
    results[i_generator] = d;
  }
  else
  {
    nlohmann::json j;

    if (d.is_array())
    {
      for (const auto &e : d)
      {
        nlohmann::json k;

        auto end = e.end();

        for (const auto &s : selected_keys)
        {
          auto val = e.find(s);

          if (val != end)
          {
            k[s] = *val;
          }
        }

        j.push_back(k);
      }
    }
    else
    {
      auto end = d.end();

      for (const auto &s : selected_keys)
      {
        auto val = d.find(s);

        if (val != end)
        {
          j[s] = *val;
        }
      }
    }

    results[i_generator] = j;
  }
}

/* ------------------------------------------------------------------ */

void ProData::prepare_impl()
{
  results.resize(n_generators);
}

/* ------------------------------------------------------------------ */

const std::vector<nlohmann::json> &ProData::get_results()
{
  return results;
}