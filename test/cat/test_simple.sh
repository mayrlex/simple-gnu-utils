#!/bin/bash

function test_case() {
    local test_case=$1
    local flags=$2
    local test_files=$3
    local head_prefix="====="

    echo "$head_prefix Run test case: $test_case"
    local output=$(diff --color=always <(./../../gcat $flags $test_files) <(cat $flags $test_files))

    if [[ -z "$output" ]]; then
        echo ">>> Output:"
        echo "No difference"
        echo ""
        echo ">>> Test files:"
        echo $test_files
    else
        echo ">>> Output:"
        echo -e "$output"
        echo ">>> Test files:"
        echo $test_files
    fi
}

test_case "flag -b" -b "case_multi_space.txt"
test_case "flag -e" -e "case_multi_space.txt"
test_case "flag -E" -E "case_multi_space.txt"
test_case "flag -n" -n "case_multi_space.txt"
test_case "flag -s" -s "case_multi_space.txt"
test_case "flag -t" -t "case_tabs.txt"
test_case "flags -bnsE" -bnsE "case_multi_space.txt"
test_case "flags -vET" -vET "case_default.txt case_tabs.txt"
test_case "flags -bevEnstT & multi files" -b "case_gen.txt case_tabs.txt case_multi_space.txt case_default.txt"
test_case "flags -bevEnstT & case gen" -bevEnstT "case_gen.txt"
