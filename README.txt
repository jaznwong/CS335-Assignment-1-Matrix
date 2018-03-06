Jasmine Wong
February 15, 2018
README.txt
Explains which parts of assignments were completed, bug errors,
instructions on how to run file, and the input/output files if applicable

i. All parts of Assignment_1 were completed.

ii. Bugs encountered:

The program compiled after typing "make all" the first few times; however, my
laptop (running on MacOSX) terminated the program with "Illegal Instruction: 4."

Upon this error, I compiled and ran my code through the remote linux environment.

Again, there were no compilation errors with Make all, but upon running the
program, there was no output. I realized that I was incorrectly reading the file
using std::fstream instead of std::cin.

After fixing this error, my program was able to output a portion of TestPart1(),
but terminated due to a seg fault. I was able to pinpoint my errors by inserting
std::cout lines within my functions and overloaded operators, and seeing which
lines actually printed.

Listed are the errors:

1) For the move constructor: Matrix(Matrix &&rhs){} I initially did not set
"array_ = rhs.array_;"

2) For the operator[] overload, std::vector<Object> operator[](int row) const {}
I realized I needed to use [row-1] as opposed to [row] because the array row
index starts with 0.

3) For both operator+ overloads, my temp_matrix was set equal to array_ as
opposed to *this

4) Occasionally mispelling names of parameters

5) Forgetting to put } and ; at the end of functions or lines

iii. To run this file on terminal, type:

1) make all
2) ./test_matrix1 < test_input_file.txt

iv. the input file (if any) and the output files (if any)

The input file is "test_input_file.txt"
