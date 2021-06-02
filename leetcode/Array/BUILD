package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "container_with_most_water",
    srcs = ["container_with_most_water.cc"],
    malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        '//third_party/glog:glog',
        '//third_party/gflags:gflags',
    ],
    linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)

cc_binary(
    name = "move_zeroes",
    srcs = ["move_zeroes.cc"],
    malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        '//third_party/glog:glog',
        '//third_party/gflags:gflags',
    ],
    linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)

cc_binary(
    name = "contains_duplicate",
    srcs = ["contains_duplicate.cc"],
    malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        '//third_party/glog:glog',
        '//third_party/gflags:gflags',
    ],
    linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
