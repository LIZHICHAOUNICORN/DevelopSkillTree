package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "implement_queue_using_stacks",
    srcs = ["implement_queue_using_stacks.cc"],
    malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        '//third_party/glog:glog',
        '//third_party/gflags:gflags',
    ],
    # linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
    linkopts = ['-lm', '-lpthread', '-lrt'],
)
