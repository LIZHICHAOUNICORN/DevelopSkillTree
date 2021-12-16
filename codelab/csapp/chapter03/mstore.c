long mult2(long x, long y) {
  return x * y;
}

void multstore(long x, long y, long* des) {
  long t = mult2(x, y);
  *des = t;
}
