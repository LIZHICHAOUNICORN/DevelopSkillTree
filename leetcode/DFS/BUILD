package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "path_sum_iii",
    srcs = ["path_sum_iii.cc"],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        '//third_party/glog:glog',
        '//third_party/gflags:gflags',
    ],
    # linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
    linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt'],
)
