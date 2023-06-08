load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "test",
    srcs = ["test.cc"],
    hdrs = ["test.h"],
    deps = ["//main:snake"]
)

cc_binary(
    name = "run_tests",
    srcs = ["run_tests.cc"],
    deps = [
        ":test",
        "//main:snake",
    ],
)
