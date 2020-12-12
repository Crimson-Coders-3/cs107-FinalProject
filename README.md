# cs107-FinalProject Master: [![Build Status](https://travis-ci.com/Crimson-Coders-3/cs107-FinalProject.svg?token=b3u4uQsijMxdCtTBnkQy&branch=master)](https://travis-ci.com/Crimson-Coders-3/cs107-FinalProject) [![codecov](https://codecov.io/gh/Crimson-Coders-3/cs107-FinalProject/branch/master/graph/badge.svg?token=K3Q5S3JJKG)](https://codecov.io/gh/Crimson-Coders-3/cs107-FinalProject)
 
Final Project for CS107 (Fall 2020)
Group #3
Group Members
1. Gayatri Balasubramanian
2. Wenlin (Scarlett) Gong
3. Morris Reeves

# Installation Guide / Getting Started (TL;DR)

This is a User Guide to our Auto Differentiation, Root-finding, and Dual Number Libraries.

### 1.1 Installation

1. Clone our GitHub repo:
```
git clone https://github.com/Crimson-Coders-3/cs107-FinalProject/
```

2. Build third party libraries:
```
cd 3PL
./build_3PL.sh
```
3. Execute config.sh from the main project directory: 
```
cd ..
./config.sh
```

### 1.2 Start Coding
4. To start coding:
```
cd App
cd src
vim main.cpp
```
In `App/src` you will find `main.cpp` preconfigured for you to call any of the Auto Differentiation, Roots, and Dual libraries.
You may notice that `main.cpp` includes only the roots library (`#include "Roots.h"`). 
Roots uses ADFunc and ADFuncVector, so including just Roots catches all three in one.

Working in `App/src`, you should have no problem creating other C++ files and including the header file of the relevant library, you are calling.
I.e., `#include "ADFunc.h", #include "ADFuncVector.h", #include "Dual.h", #include "Roots.h"`.

### 1.3 Compile and Execute

5. To compile your C++ code within `App/src`, edit the `App/src/CMakeLists.txt` file to include any additional `.cpp` files you created.
```
nano CMakeLists.txt
```
6. Now return the `App` directory and run `./config.sh`
```
cd ..
./configure.sh
```
7. To run your executable, enter the `App/bin` directory and run your executable.
```
cd bin
./app_demo
```

### 1.4 Calling Functions / Function Documentation

8. `App/src/example.cpp` includes some function declarations to get you started.
```
#include <math.h>
#include <string>
#include <cmath>
#include "Roots.h"

using namespace std;

vector<ADFunc> customFunct2(Eigen::VectorXd vals){
     ADFunc x = ADFunc(vals[0], {1,0,0});
     ADFunc y = ADFunc(vals[1], {0,1,0});
     ADFunc z = ADFunc(vals[2], {0,0,1});
     return {5*sin(x), 3*y/2, z+2};
}


int main(){
    function<vector<ADFunc>(Eigen::VectorXd)> Func = customFunct2;
    Equation eq(customFunct2, 3);
    Eigen::VectorXd guess(3);
    guess << 1, 1, 1;
    double tol = 1e-4;
    Eigen::VectorXd roots = eq.getRoots(guess, tol);
    cout << "Roots found: \n" << roots << endl;

    //Example of getting the Jacobian (as a MatrixXd object)
    ADFunc x = ADFunc(7, {1,0});
    ADFunc y = ADFunc(3, {0,1});
    vector<ADFunc> F2 = {2*pow(x,2), 5*sin(y)*x};
    Eigen::MatrixXd J = getJ(F2, 2);
    cout << "Jacobian of F: \n" << J << endl;
    return 0;
}
```
9. A detailed list of all function declarations and functionality description is in our Doxygen.
When you `git clone`-ed our library, you automatically received our Doxygen documentation.
From the main directory, navigate to `docs/GENERAETED_DOCS/html/index.html`
```
cd docs
cd GENERAETED_DOCS/html
Click on `docs/GENERAETED_DOCS/html/index.html` and it will launch locally in your browser.
```
10. Navigate to `Files/File List`. Click on the file of interest to you, and scroll down to "Functions."
Click on any of the functions to arrive at the Reference page, where you will find a description of all that library's functions.

### 1.5 Requirements:

Here are some requirements you will need. Also see "4.3 Possible Error Messages" in you run into a proble,..

1. cmake:

* tutorial: https://cliutils.gitlab.io/modern-cmake/chapters/intro/installing.html
* documentation: https://cmake.org/cmake/help/v3.19/
* useful links: https://github.com/ackirby88/CS107/tree/master/cmake

2. Eigen (linear algebra library)

* overview: http://eigen.tuxfamily.org/dox/index.html
* source code bundled with our GitHub repo under "3PL" (containing the extracted tar.gz file from http://eigen.tuxfamily.org/index.php?title=Main_Page#Download)
* *following step 2 in the Installation Guide above will build Eigen by default, to the `install` directory*

3. GoogleTest (for testing only, not required)

* additional info.: https://github.com/google/googletest/tree/master/googletest
* *following step 2 in the Installation Guide above will build GoogleTest to the `install` directory*

4. lcov (for testing only, not required)

* *following step 2 in the Installation Guide above will build lcov by default, to the `install` directory*
* once the installation completes, you may try "make test" to verify 
if it is installed correctly
* additional info: http://ltp.sourceforge.net/coverage/lcov.php
* source code repo: https://github.com/linux-test-project/lcov

5. C++ 11

### 1.6 Beyond

If you need any help using our library or desire to provide feedback (which we are always very eager for!) contact us here:
- Scarlett Gong: wenlin_gong@g.harvard.edu 
- Morris Reeves: morrisreeves@g.harvard.edu 
- Gayatri Balasubramanian: gayatrib@college.harvard.edu

### 1.7 Broader Impact and Inclusion Statement

See our mission and principles in section 2 (right below).

## 2 Broader Impact and Inclusion

### 2.1 Broader Impact
From Linux to Python and R, open source was one of the most ingenious consequences of the internet. It was a larger-than-life platform to exchange code and come together to build better, more comprehensive software. However, open source has been a platform of something else: an extension of the biases and inequalities in our own society. Perhaps compounded even more by how rapidly open-source code and software develop – like a kid chasing an accelerating train. From spare or difficult documentation to difficult syntax and a lack of transparency in the code, open source software can be impassible. As develops, our foremost intention is to make our software accessible to the world, equally.
Here, we developed an open-source auto-differentiation library in C++, a field and a programming language both not very accessible to those most affected by the inequalities in computing.  Our strength in making our library transparent and accessible actually came from our weakness. Two of us began this project with no C++ background and one of us had a single year of experience. We experienced firsthand the impassibility of this content – we even watched our teaching staff falter. So, while the process of developing this library was uphill for us, it taught us – made transparent to us – where our users will struggle as well.
We acknowledge that software, by definition, has a barrier, because nobody can learn to code nor read code overnight. But we aimed to make an accessible C++ auto-differentiation library through the eyes of our users.
A user navigates to open source code on GitHub and first navigates to the README.md file. Striving for software inclusivity, we wrote extensive, readable documentation. We organized our documentation as readably as possible. We included a “tl;dr” because often this is the first thing a user looks for. After following documentation to download, a user often next looks for common sense folder names telling them where to begin. Our “Example” folder containing “example.cpp” sets all this up for the user. Next, a user looks for the methods/functions in the library, and our “.h” header files contain extensive comments.
We hope that through thinking through the user’s thought process, we have anticipated and understood the diversity of backgrounds they have. We included our contact info, as users who need help with our documentation can reach out to us directly for help. And to those on the more developer side, we included the ability to make pull requests, which we review on a frequent basis.
We acknowledge that our software, like all software, can be abused. As a programmer, you must understand that being a good citizen also means being an ethical coder. If you have doubts about usage, reach out to us. While accessible and free of charge, we have the right to act judiciously if you use our code for harm.

### 2.2 Inclusivity Statement
Crimson Coders 3 welcome and encourage you to use and contribute to our auto-differentiation library. Our work is guided by the principles of equality, transparency, respect, giving, and kindness. To us, diversity is not only a multi-identity user community, but the accessibility of our code to the world. We encourage you to contribute if you can or reach out if you need help understanding our library.
