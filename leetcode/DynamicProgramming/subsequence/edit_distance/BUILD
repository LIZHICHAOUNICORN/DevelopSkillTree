package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "edit_distance",
    srcs = ["edit_distance.cc"],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        "@com_github_google_glog//:glog",
        "@com_github_gflags_gflags//:gflags",
    ],
    linkopts = ['-lm', '-lpthread'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
cc_binary(
    name = "delete_operation_for_two_strings",
    srcs = ["delete_operation_for_two_strings.cc"],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        "@com_github_google_glog//:glog",
        "@com_github_gflags_gflags//:gflags",
    ],
    linkopts = ['-lm', '-lpthread'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
cc_binary(
    name = "minimum_ascii_delete_sum_for_two_strings",
    srcs = ["minimum_ascii_delete_sum_for_two_strings.cc"],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        "@com_github_google_glog//:glog",
        "@com_github_gflags_gflags//:gflags",
    ],
    linkopts = ['-lm', '-lpthread'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)

cc_binary(
    name = "is_subsequence",
    srcs = ["is_subsequence.cc"],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        "@com_github_google_glog//:glog",
        "@com_github_gflags_gflags//:gflags",
    ],
    linkopts = ['-lm', '-lpthread'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)

cc_binary(
    name = "distinct_subsequences",
    srcs = ["distinct_subsequences.cc"],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        "@com_github_google_glog//:glog",
        "@com_github_gflags_gflags//:gflags",
    ],
    linkopts = ['-lm', '-lpthread'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
