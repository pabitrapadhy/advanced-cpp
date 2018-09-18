//
//  advanced_macros.h
//  advanced_cpp
//
//  Created by Padhy, Pabitra on 18/09/18.
//  Copyright © 2018 Padhy, Pabitra. All rights reserved.
//

#pragma once
#include <iostream>
using namespace std;

namespace CPP_ADVANCED {
    // NOTE: the value passed in the macro are called literals.
    
#define CONCAT(x,y) x ## y

    void test_concat() {
        cout << CONCAT(10, 10) << endl;
        // result : 1010, because 1010 is interpreted as number, so works OK.
        
        // cout << CONCAT(abc, pqr) << endl;
        // result: abcpqr, the above line won't work because after concatenating the literals
        // doesn't make any sense to the compiler, these are not any value for a known type to the compiler.
        
        // cout << CONCAT(10.2, 10.2) << endl;
        // result: 10.210.2, the above statement won't work, because after concatenating the literals
        // the result doesn't make any sense to the compiler.
    }
    
#define STRINGIFY(a) STRINGIFY_I(a)
#define STRINGIFY_I(a) #a
    
    void test_stringify() {
        std::string str;
        
        str = STRINGIFY(10);
        cout << "Stringified Value : " << str << endl;
        // result: "10" , after stringifying the value is convertible to std::string.
        
        str = STRINGIFY(abc);
        cout << "Stringified Value : " << str << endl;
        // result: "abc" , after stringifying the value is convertible to std::string.
        
        str = STRINGIFY(10+2);
        cout << "Stringified Value : " << str << endl;
        // result: "10+2" , after stringifying the value did not change to 12, because the macro just converts
        // literals into string directly, there is no other operation on those.
    }
    
    void test_concat_then_stringify() {
        std::string str;
        
        // OLD: (inhibits expansion)
        // #define STRINGIFY(a) #a
        {
            str = STRINGIFY(CONCAT(10, 20));
            // cout << "Stringified Value after Concat is : " << str << endl;
            // result: "CONCAT(10, 20)", we may be expecting "1020" as we believed that the CONCAT will work.
            // Please be noted that, these are not like function calls, macros simply replace value, no operations.
            // But, our assumption is achievable if we make change to the macro definition itself.
        }
        
        // NEW: (supports expansion)
        // #define STRINGIFY(a) STRINGIFY_I(a)
        // #define STRINGIFY_I(a) #a
        {
            str = STRINGIFY(CONCAT(10, 20));
            cout << "Stringified Value after Concat is : " << str << endl;
            // result: "1020", supported expansion after changing the macro.
            
            str = STRINGIFY(CONCAT(abc, pqr));
            cout << "Stringified Value after Concat is : " << str << endl;
            // result: "abcpqr", see here the concat worked correctly, but it didn't earlier.
            // because it is not stringified, so the final literal is a valid literal, understood by compiler.
        }
    }
    
// 1. PATTERN MATCHING
#define PATTERN(cond) PATTERN_ ## cond
#define PATTERN_0 off
#define PATTERN_1 on
#define PATTERN_2 int
#define PATTERN_3 <vector>
    
    void test_pattern_matching() {
        cout << "Pattern Matching : " << STRINGIFY(PATTERN(1)) << endl;
        // result: on, this works sort of like a switch case, but with no defaults.
        // if the pattern is not found, then a compilation error will throw.
        // e.g; can be used to #include platform specific files.
        
        // PATTERN(1); // Compilation Error : Use of undeclared identifier on.
        // PATTERN(2); // WARNING: doesn't declare anything. (it would expand to int;)
        // PATTERN(100); // Compilation Error : Use of undeclared identifier PATTERN_100
        // #include PATTERN(3) // NOTE: we can include header files like this as well.
        
        cout << "Pattern Matching : " << STRINGIFY(PATTERN(100)) << endl;
        // result: WHOA !!!, here I was expecting that compilation error will throw because there is no PATTERN_100
    }
    
    bool execute() {
        test_concat();
        test_stringify();
        test_concat_then_stringify();
        test_pattern_matching();
        
        return true;
    }
}
