package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "count_of_range_sum",
    srcs = [
        "count_of_range_sum.cc",
    ],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        "@com_github_google_glog//:glog",
        "@com_github_gflags_gflags//:gflags",
    ],
    linkopts = ['-lm', '-lpthread'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
