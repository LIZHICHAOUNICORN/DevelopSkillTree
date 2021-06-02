package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "number_of_1_bits",
    srcs = ["number_of_1_bits.cc"],
    malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        '//third_party/glog:glog',
        '//third_party/gflags:gflags',
    ],
    linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)

cc_binary(
    name = "power_of_two",
    srcs = ["power_of_two.cc"],
    malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        '//third_party/glog:glog',
        '//third_party/gflags:gflags',
    ],
    linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
