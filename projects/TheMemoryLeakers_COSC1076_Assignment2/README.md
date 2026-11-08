# TheMemoryLeakers_COSC1076_Assignment2 Individual Component

## This repository was forked from Group "The Memory Leakers" for APT Assignment 2 Enhancement:
#### Link to the repository : https://github.com/LabibaShaikh/TheMemoryLeakers_COSC1076_Assignment2

- Shaikh Naima Labiba - s3954789

## Build and run (From root project folder):

- Run build: `make`
- Run executable: `./bin/ftt`

## Automated Test Script
### Running the Automated Test Script:
To run the automated test script, navigate to the `tester/` directory containing the `autoTester.bash` file and execute the following command:
```bash
sudo ./autoTester.bash
```
Alternatively, from the root directory, run:
```bash
sudo ./tester/autoTester.bash
```
You may need to grant execute permissions to the script before running it. This can be done with the following command:
```bash
chmod +x autoTester.bash
```
Alternatively:
```bash
chmod +x tester/autoTester.bash
```

#### Script Arguments
The script accepts the following optional arguments:
* `-showdiff=true|false`: Show differences between expected and actual output (default: true)
* `-verbose=true|false`: Display verbose output (default: true)
* `-help, -h`: Show the help message
For example, to run the script without showing differences and with verbose output, use:
```bash
sudo ./autoTester.bash -showdiff=false -verbose=true
```

###Setting Up a Test Folder
The script expects test folders to be located in a directory named `tests` within a directory named `tester`. Each test folder should be named with a number prefix (e.g., `01-TestName`), and contain the following files:
* `testXX.in`: The input file for the test, where XX is the test number.
* `testXX.out`: The expected output file for the test.
* `testXXfoods.dat` and `testXXcoins.dat`: __Optional__ data files for the test. **If these are not provided, the script will use default data files.**
Here is an example of a test folder structure:
```
tester/
└── tests/
    └── 01-TestName/
        ├── test01.in
        ├── test01.out
        ├── test01foods.dat (optional)
        └── test01coins.dat (optional)
```
To create a new test, simply create a new folder in the `tests` directory following the structure above.

## Automatic Google-Style formatting Requires:

- Clang formatting installed: `sudo apt install clang-format -y`
- VSCode Extension:
  Name: Clang-Format
  Id: xaver.clang-format
  Description: Use Clang-Format in Visual Studio Code
  Version: 1.9.0
  Publisher: Xaver Hellauer
  VS Marketplace Link: https://marketplace.visualstudio.com/items?itemName=xaver.clang-format

### Run auto-formatting:

- To automatically format a file on save, add the following to your vscode settings.json file:
  ```
  {
      "editor.formatOnSave": true
  }
  ```
- Alternatively, you can press `Alt+Shift+F` to format the document, when `clang-format` is the default formatter
- Or via the command, run (Access with `Ctr+Shift+p`) `Format document with...` and select `clang-format`

## Branches Overview

### `main`
 The working and up to date branch, ready to be graded.

#### `tests/`

- **Description**: Contains test cases and scripts for the program.
- **Functionality**:
  - Automates testing procedures.
  - Validates the functionality of the application against predefined scenarios.


#### `Makefile`

- **Description**: Manages the build process of the project.
- **Functionality**:
  - Compiles code.
  - Cleans build files.
  - Runs tests.




