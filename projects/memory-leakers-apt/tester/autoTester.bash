#!/bin/bash
# Because of copy file access control Run with sudo ./autoTester.bash (FIXME: Fix file access from copy files, low priority)

# Get the absolute path of the script's directory
parent_path=$(cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P)

# Move to the parent directory
cd "$parent_path"

# Move into root program directory
cd ".."

# Directory containing test folders
TESTER_DIR="tester"
TEST_DIR="$TESTER_DIR/tests"

# Initialize counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=""
PASSED_TEST_LIST=""

# Default data files
DEFAULT_DATA_DIR="defaultdata"
DEFAULT_FOODS_FILE="$DEFAULT_DATA_DIR/defaultfoods.dat"
DEFAULT_COINS_FILE="$DEFAULT_DATA_DIR/defaultcoins.dat"

SEPARATOR="=============================================================================="
WEAK_SEPARATOR="------------------------------------------------------------------------------"

# Check command-line argument for -showdiff
SHOW_DIFF=true
VERBOSE=true
if [[ "$1" == "-showdiff=false" ]]; then
    SHOW_DIFF=false
fi
if [[ "$1" == "-verbose=false" ]]; then
    VERBOSE=false
fi

# Helper function to print usage information
print_help() {
    echo -e "\e[1;33mUsage:\e[0m ./autoTester.bash [-showdiff=true|false] [-verbose=true|false] [-help|-h]"
    echo -e "\e[1;33mOptions:\e[0m"
    echo -e "  -showdiff=true|false   Show differences between expected and actual output (default: true)"
    echo -e "  -verbose=true|false    Display verbose output (default: true)"
    echo -e "  -help, -h              Show this help message"
    exit 0
}

# Check command-line arguments
if [[ "$1" == "-help" || "$1" == "-h" ]]; then
    print_help
fi

# Iterate over each test folder
if [ "$VERBOSE" = true ]; then
    echo "Running tests in $TEST_DIR..."
fi
for TEST_FOLDER in "$TEST_DIR"/*; do
    if [[ "$TEST_FOLDER" == *-* ]] && [ -d "$TEST_FOLDER" ]; then
        if [ "$VERBOSE" = true ]; then
            echo -e "\e[94m\e[1m$SEPARATOR\e[0m"
            echo -e "\e[1m\e[35mRunning test ${TEST_FOLDER##*/}...\e[0m"
            echo -e "\e[94m\e[1m$SEPARATOR\e[0m"
        fi

        # Extract the test number from the folder name
        TEST_NUMBER=$(basename "$TEST_FOLDER" | cut -d'-' -f1)

        # Assuming the input file is named 'test01.in' and the expected output file is 'test01.out'
        INPUT_FILE="$TEST_FOLDER/test${TEST_NUMBER}.in"
        EXPECTED_OUTPUT_FILE="$TEST_FOLDER/test${TEST_NUMBER}.out"
        ACTUAL_OUTPUT_FILE="$TEST_FOLDER/actual_output.txt"

        # Check if the input files exist, otherwise use the default files
        FOODS_FILE="$TEST_FOLDER/test${TEST_NUMBER}foods.dat"
        COINS_FILE="$TEST_FOLDER/test${TEST_NUMBER}coins.dat"

        if [ ! -f "$FOODS_FILE" ]; then
            FOODS_FILE=$TESTER_DIR/$DEFAULT_FOODS_FILE
            if [ "$VERBOSE" = true ]; then
                echo -e "\e[33m\e[1mWarning: Foods file not found for test ${TEST_FOLDER##*/}. Using default foods file.\e[0m"
                echo -e "$WEAK_SEPARATOR"
            fi
        fi
        if [ ! -f "$COINS_FILE" ]; then
            COINS_FILE=$TESTER_DIR/$DEFAULT_COINS_FILE
            if [ "$VERBOSE" = true ]; then
                echo -e "\e[33m\e[1mWarning: Coins file not found for test ${TEST_FOLDER##*/}. Using default coins file.\e[0m"
                echo -e "$WEAK_SEPARATOR"
            fi
        fi

        # Copy the .dat files to the /bin folder
        mkdir -p $TESTER_DIR/bin
        cp "$FOODS_FILE" $TESTER_DIR/bin
        cp "$COINS_FILE" $TESTER_DIR/bin

        # Set read/write permissions for the .dat files
        chmod +rw $TESTER_DIR/bin/*.dat

        # Change foods file to be just the filename of the file plus the tester bin dir
        FOODS_FILE=$TESTER_DIR/bin/$(basename "$FOODS_FILE")
        COINS_FILE=$TESTER_DIR/bin/$(basename "$COINS_FILE")

        # Check if the input and expected output files exist
        if [ ! -f "$INPUT_FILE" ] || [ ! -f "$EXPECTED_OUTPUT_FILE" ]; then
            echo -e "\e[31m\e[1mError: Input or expected output file not found for test $TEST_FOLDER\e[0m"
        else
            # Run the program with the input files and save the output
            if [ "$VERBOSE" = true ]; then
                echo -e "\e[1m\e[37mRunning...\e[0m"
                echo -e "\e[1m\e[37mRunning ./bin/ftt "$FOODS_FILE" "$COINS_FILE" < "$INPUT_FILE" > "$ACTUAL_OUTPUT_FILE"\e[0m"
            fi
            ./bin/ftt "$FOODS_FILE" "$COINS_FILE" < "$INPUT_FILE" > "$ACTUAL_OUTPUT_FILE"

            # Print test comparison message
            if [ "$VERBOSE" = true ]; then
                echo -e "\e[1m\e[37mComparing...\e[0m"
                echo -e "\e[1m\e[37mComparing $ACTUAL_OUTPUT_FILE with $EXPECTED_OUTPUT_FILE\e[0m"
            fi

            # Compare the actual output with the expected output
            if cmp -s "$ACTUAL_OUTPUT_FILE" "$EXPECTED_OUTPUT_FILE"; then
                if [ "$VERBOSE" = true ]; then
                    echo -e "$WEAK_SEPARATOR"
                    echo -e "\e[32m\e[1mTest passed!\e[0m"
                fi
                let "PASSED_TESTS++"
                PASSED_TEST_LIST+="Test ${TEST_FOLDER##*/}\n"
            else
                if [ "$VERBOSE" = true ]; then
                    echo -e "$WEAK_SEPARATOR"
                    echo -e "\e[31m\e[1mTest failed. See differences below:\e[0m"
                fi
                if [ "$SHOW_DIFF" = true ]; then
                    if [ "$VERBOSE" = true ]; then
                        echo -e "\033[32m<\033[0m indicates the expected output."
                        echo -e "\033[31m>\033[0m indicates the actual output."
                        echo -e "$WEAK_SEPARATOR"
                    fi
                    if [ "$VERBOSE" = true ]; then
                        # Use diff to compare the files and set a custom color the output, < to green, > lines to red, and the rest to cyan bold using awk
                        diff --ignore-all-space "$EXPECTED_OUTPUT_FILE" "$ACTUAL_OUTPUT_FILE" | awk '{if (substr($0, 1, 1) == ">") print "\033[31m" $0 "\033[0m"; else print}' | awk '{if (substr($0, 1, 1) == "<") print "\033[32m" substr($0, 1, 1) "\033[0m" "\033[37m" substr($0, 2) "\033[0m"; else print "\033[1m\033[36m" $0 "\033[0m"}'
                    fi
                else
                    if [ "$VERBOSE" = true ]; then
                        echo -e "$WEAK_SEPARATOR"
                        echo -e "\e[33m\e[1mShow differences option is disabled. Enable it using -showdiff=true.\e[0m"
                    fi
                fi
                FAILED_TESTS+="Test ${TEST_FOLDER##*/}\n"
            fi
            let "TOTAL_TESTS++"
            # Clear the /bin folder if there are files to be cleared
            if [ -n "$(ls -A $TESTER_DIR/bin)" ]; then
                rm $TESTER_DIR/bin/*.dat
            fi
        fi
        if [ "$VERBOSE" = true ]; then
            echo -e "$WEAK_SEPARATOR"
        fi
    fi
done

# Calculate percentage of tests passed
if [ "$TOTAL_TESTS" -eq 0 ]; then
    PERCENT_PASSED=0
else
    PERCENT_PASSED=$(awk "BEGIN {printf \"%.2f\", ${PASSED_TESTS}/${TOTAL_TESTS}*100}")
fi

# Color scaling based on percentage of tests passed
if (( $(awk "BEGIN {print ${PERCENT_PASSED} >= 90}") )); then
    COLOR="\e[32m"  # Green
elif (( $(awk "BEGIN {print ${PERCENT_PASSED} >= 70}") )); then
    COLOR="\e[33m"  # Yellow
else
    COLOR="\e[31m"  # Red
fi

# Display test results:
echo -e "\n\e[1m\e[33mTest Results:\e[0m\e[0m"
echo -e "${COLOR}Passed $PASSED_TESTS out of $TOTAL_TESTS tests ($PERCENT_PASSED% passed)\e[0m"

# Print list of passed tests
if [ "$PASSED_TEST_LIST" != "" ]; then
    echo -e "\n\e[1m\e[32mPassed Tests:\e[0m\e[0m"
    echo -e "$PASSED_TEST_LIST"
fi

# Print list of failed tests
if [ "$FAILED_TESTS" != "" ]; then
    echo -e "\e[1m\e[31mFailed Tests:\e[0m\e[0m"
    echo -e "$FAILED_TESTS"
fi
