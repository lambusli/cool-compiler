#!/bin/bash

DIFF_CMD="diff -b -w -I Increasing"

# Empty is "false"
DIFF_S=1
DIFF_LC_ONLY=
PRINT_TEST=

usage()
{
    cat << EOF
usage: $(basename "$0") [options] TEST_DIR TEST_PROG [ARGUMENT...]

Run integration tests

Options:
  -s    Don't diff assembly files even if available (will be diff'd by default)
  -p    Print test case on error
  -l    Only diff line count for stderr (instead of full contents of the file)
  -q    Quiet mode (no diff output)
  -h    Print this message
EOF
}

while getopts "sphlq" Option
do
    case $Option in
        s)
            DIFF_S=
            ;;
        p)
            PRINT_TEST=1
            ;;
        l)
            DIFF_LC_ONLY=1
            ;;
        q)
            DIFF_CMD="cmp -s"
            ;;
        h)
            usage
            exit 0
            ;;
        ?)
            usage
            exit 85
            ;;
    esac
done

shift $((OPTIND-1))
if [[ $# -lt 2 ]]; then
    >&2 echo "Error: Missing positional arguments"
    >&2 usage
    exit 1
fi

TEST_DIR="$1"
shift 1

# Create temporary directory for output files, accounting for differences
# between Linux and OSX
OUT_DIR=$(mktemp -d 2> /dev/null || mktemp -d -t 'tmp') || exit 1
trap "rm -rf $OUT_DIR" 0

cd "$TEST_DIR"

# Find all tests
tests=( $(find "." -name "*.test") )

# Track number of passing tests
total=0
passed=0

for test in "${tests[@]}"; do
    (( ++total ))

    name=$(basename "$test")
    echo "Testing ${name} ------------------------"
    if [[ -e "${test}.desc" ]]; then
        cat "${test}.desc"
    fi

    "$@" -w "$OUT_DIR" "$test" > "${OUT_DIR}/${name}.stdout" 2> "${OUT_DIR}/${name}.stderr"

    test_exit=0

    # If we have a assembly file to compare against, do so...
    if [[ $DIFF_S &&  -e "${test}.s" ]]; then
        #diff -y -b -w "${test}.s" "${OUT_DIR}/${name}.s"
        $DIFF_CMD "${test}.s" "${OUT_DIR}/${name}.s"
        if [[ $? -ne 0 ]]; then
            test_exit=1
        fi
    fi

    # Compare against known stdout and stderr
    #diff -y -b -w "${test}.stdout" "${OUT_DIR}/${name}.stdout"
    $DIFF_CMD "${test}.stdout" "${OUT_DIR}/${name}.stdout"
    if [[ $? -ne 0 ]]; then
        test_exit=1
    fi

    if [[ $DIFF_LC_ONLY && $test_exit -eq 0 ]]; then
        # Only compare numbers of lines...
        if [[ $(awk 'END { print NR; }' "${test}.stderr") -gt $(awk 'END { print NR; }' "${OUT_DIR}/${name}.stderr") ]]; then
            # Print side by side output and mark as failing
            #diff -y -b -w <(sort "${test}.stderr") <(sort "${OUT_DIR}/${name}.stderr")
            $DIFF_CMD <(sort "${test}.stderr") <(sort "${OUT_DIR}/${name}.stderr")
            test_exit=1
         fi
    else
        # Ignore different orders in the error messages
        #diff -y -b -w <(sort "${test}.stderr") <(sort "${OUT_DIR}/${name}.stderr")
        $DIFF_CMD <(sort "${test}.stderr") <(sort "${OUT_DIR}/${name}.stderr")
        if [[ $? -ne 0 ]]; then
            test_exit=1
        fi
    fi

    if [[ $test_exit -eq 0 ]]; then
        (( ++passed ))
    else
        echo "Failed"
    fi

    if [[ $PRINT_TEST && $test_exit -ne 0 ]]; then
        echo "Failing test case:"
        cat "${test}"
    fi
done

echo "Total tests: $total"
echo "Passing tests: $passed"
echo "Failing tests: $((total - passed))"

if [[ $passed -ne $total ]]; then
    exit 1
else
    exit 0
fi