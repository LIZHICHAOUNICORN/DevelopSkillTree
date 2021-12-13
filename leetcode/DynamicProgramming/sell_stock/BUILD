package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "best_time_to_buy_and_sell_stock",
    srcs = ["best_time_to_buy_and_sell_stock.cc"],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        '//third_party/glog:glog',
        '//third_party/gflags:gflags',
    ],
    linkopts = ['-lm', '-lpthread', '-lrt'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
