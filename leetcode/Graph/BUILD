package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "cheapest_flights_within_k_stops",
    srcs = ["cheapest_flights_within_k_stops.cc"],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        '//third_party/glog:glog',
        '//third_party/gflags:gflags',
    ],
    linkopts = ['-lm', '-lpthread', '-lrt'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)

