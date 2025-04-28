#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

GGREP=./ggrep
if [ ! -x "$GGREP" ]; then
    echo "ggrep not found; running make..."
    make -C src/grep
    GGREP=./src/grep/ggrep
    if [ ! -x "$GGREP" ]; then
        echo "Compilation failed."
        exit 1
    fi
fi

TEST_DIR=$(mktemp -d)

cat <<EOF > "$TEST_DIR/file1.txt"
TestPattern line one.
Another line with TestPattern.
A line without the keyword.
EOF

cat <<EOF > "$TEST_DIR/file2.txt"
Different file with TestPattern.
No keyword here.
EOF

cat <<EOF > "$TEST_DIR/patterns.txt"
TestPattern
EOF

pass_count=0
fail_count=0
total_count=0
failed_tests_info=""

gen_flags() {
    num=$1
    local flags=""
    local flag_letters=("i" "v" "c" "l" "n" "h" "s" "o")
    for i in {0..7}; do
        if (( num & (1 << i) )); then
            flags+="${flag_letters[i]}"
        fi
    done
    if [ -n "$flags" ]; then
        echo "-$flags"
    else
        echo ""
    fi
}

run_test() {
    test_name="$1"
    shift
    args=("$@")
    
    expected=$(grep "${args[@]}" 2>&1)
    
    result=$("$GGREP" "${args[@]}" 2>&1)
    
    tmp_exp=$(mktemp)
    tmp_res=$(mktemp)
    echo "$expected" > "$tmp_exp"
    echo "$result" > "$tmp_res"
    
    total_count=$((total_count+1))
    if diff -q "$tmp_exp" "$tmp_res" > /dev/null; then
        echo -e "${GREEN}PASSED: $test_name${NC}"
        pass_count=$((pass_count+1))
    else
        echo -e "${RED}FAILED: $test_name${NC}"
        fail_count=$((fail_count+1))
        failed_tests_info+="\nFAILED: $test_name\nCommand: grep ${args[*]}\nExpected:\n$(cat "$tmp_exp")\n"
        failed_tests_info+="ggrep output:\n$(cat "$tmp_res")\n\n"
    fi
    rm -f "$tmp_exp" "$tmp_res"
}

for num in $(seq 0 255); do
    flag_str=$(gen_flags $num)
    run_test "[$flag_str] -e single file" $flag_str -e "TestPattern" "$TEST_DIR/file1.txt"
    
    run_test "[$flag_str] -e multiple files" $flag_str -e "TestPattern" "$TEST_DIR/file1.txt" "$TEST_DIR/file2.txt"
done

echo -e "\nTotal tests run: $total_count"
echo -e "${GREEN}Passed: $pass_count${NC}"
echo -e "${RED}Failed: $fail_count${NC}"

if [ $fail_count -gt 0 ]; then
    echo -e "\n${RED}Failed test details:${NC}"
    echo -e "$failed_tests_info"
fi

rm -rf "$TEST_DIR"
