import unittest
import traceback

from random import shuffle

from ppap4lmp import Element, StaCustom, ProValueArray, InvOMP

class TestProValueArray(unittest.TestCase):

  def test_error(self):

    elems = [
      Element(StaCustom({"id": i, "A": i*i})) for i in range(1000)]
    pro = ProValueArray(elems)

    try:
      InvOMP(pro).execute()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: ProValueArray: No selected values")

    pro = ProValueArray(elems)
    pro.select("B")

    try:
      InvOMP(pro).execute()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: ProValueArray: Selected key(s) and 'id' do not "
        + "exist")

    elems = [
      Element(StaCustom(
        {"id": i, "A": "str-{}".format(i)})) for i in range(1000)]
    pro = ProValueArray(elems)
    pro.select("A")

    try:
      InvOMP(pro).execute()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: ProValueArray: Value is not number")

    data = [
      [{"id": j, "A": float(i*j)} for j in range(10*i+1)]
      for i in range(100)]
    elems = [Element(StaCustom(d)) for d in data]
    pro = ProValueArray(elems)
    pro.select("A")

    try:
      InvOMP(pro).execute()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: ProValueArray: Data sizes must be the same")

  def test_select_one(self):

    ids = list(range(1000))
    shuffle(ids)

    data = [[
      {"id": j, "A": float(i+j), "B": float(i*j)}
      for j in ids]
      for i in range(100)]
    elems = [Element(StaCustom(d)) for d in data]
    pro = ProValueArray(elems)
    pro.select("A")

    InvOMP(pro).execute()

    arr_A = pro.get_results()["A"]

    for i, elem in enumerate(elems):

      ds = elem.get_data()

      for d in ds:
        self.assertEqual(arr_A[i][d["id"]], d["A"])

  def test_select_two(self):

    ids = list(range(1000))
    shuffle(ids)

    data = [[
      {"id": j, "A": float(i+j), "B": float(i*j)}
      for j in ids]
      for i in range(100)]
    elems = [Element(StaCustom(d)) for d in data]
    pro = ProValueArray(elems)
    pro.select("A", "B")

    InvOMP(pro).execute()

    arrs = pro.get_results()

    for i, elem in enumerate(elems):

      ds = elem.get_data()

      for d in ds:
        self.assertEqual(arrs["A"][i][d["id"]], d["A"])
        self.assertEqual(arrs["B"][i][d["id"]], d["B"])