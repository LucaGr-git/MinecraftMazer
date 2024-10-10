C++ Style Guide
  
CORE RULES

    • Optimise for the reader, not the writer. In general, more time is spent reading code than writing it. Explicitly write code for the experience of the average software engineer reading, maintaining, and debugging your code rather than making it easier to write your code.

    • Be consistent. Using one style consistently through your code lets developers focus on other (more important) issues. Where you have a choice, make a decision and stick to it. Chopping and changing your style makes it harder for the reader to understand your code!

    • Avoid surprising or dangerous constructs. C++ has many features, and some that are more surprising or dangerous than you might think at a glance. Some style guide restrictions are in place to prevent falling into these pitfalls. Importantly, some C++ features are banned. Make sure you are aware of this, even if you don't fully understand why the feature is banned.
    

Conventions

#   Class Names
        • Choose meaning names for classes.

        • Class names must start with a upper case letter
        
        • Use camel case (ClassName) 

#   Code file names
        • Use file extension .cpp

        • Only use alpha-numeric characters in the file name. If the file contains a class, the file name should be called the same as the class.

#   Header file
        • Use file extension .h
        
        • Use the same name as the corresponding code file. Generally each code file should have a corresponding header file. 
        
        • For independent header file, only use alpha-numeric characters in the file name.

#   Macros
        • Macros should be used sparingly, and only if their use makes the code clearer. Where possible functions should be used in place of macros.

#   Magic Numbers
        • Hard-coded "magic numbers" should be replaced with meaningfully named constants (#define's)

#   Namespace identifier imports
        • Only import the identifiers from a namespace that are required. Globally importing of all identifiers from a namespace, such as the example below is not permitted.
        
        • // This is NOT permitted:
        using namespace std;

#   Return statement (singular)
        • A function must only contain a single return statement, at the end of the function.
        
        • The use of multiple return statements in a function is NOT permitted.

#   Static Global Variables
        • The use of static global variables should be used sparingly and only if there is not a good design that would eliminate their use.

#   Variable Initialisation
        • Variables must be initialised when they are declared

#   Variable Naming
        • Choose meaningful names for variables.
        
        • Variable names must start with a lower case letter
        
        • Use camel case (variableName)

Formatting

#   #define
        • Must always use uppercase letters only and underscores. Numbers are not permitted.

#   Class elements
        • A level of indentation must be used to denote the public, protected, and private elements of a class.

#   Comments
        • Use either // or /* ... */ style comments.

        • Comments must be placed above the lines to which they refer. Inline comments should not be used.
        
        • Multi-line comment enclosed inside a single /* ... */ should be formatted as:
            /* * Comment begins here * Comment continues with '*' as start of line (and spaces to align) */

#   Indentation
        • Use between 2-4 spaces for indentating code.

#   Line length
        • A single line of code must not exceed 80 characters.

#   Multi-line statements
        • Multi-statements such as functions definitions, function calls, and expressions at a minimum must be intending by a single level, and ideally appropriately aligned to their matching syntax.

#   Variable initialisation
        • Variables should be initialised close to where they are first used, while maintaining wider-code readability.

#   White space
        • The use of Tabs for white space is not permitted.

Banned List

#   Keywords
        • The following keywords are banned and cannot be used. Use of these in your assignments will immediately results in a mark of zero for code style.

            break
            continue
            goto
            next

#   Side effects
        • Code that results in side effects is NOT permitted.

#   #pragma directives
       • All #pragma directives are not permitted. These directives are banned as they are typically compiler specific.

#   Meta Programming
        • Meta programming using the C++ pre-processor is not permitted

#   Non-Static Global Variables
        • All non-static variables must be enclosed within the scope of a function or classs.

#   External Libraries
        • Unless otherwise stated, the use of external libraries outside of the C++ STL (such as Boost) are not permitted.

Compilation

    Unless otherwise stated, all executable files should be compiled as:
    
#   g++ -Wall -Werror -std=c++17 -O -o <executable_name> <filename1.cpp> <filename2.cpp> ...
    
    Unless otherwise stated, to compile to an object file, a similar command should be used: 
    
#   g++ -Wall -Werror -std=c++17 -O -c <filename.cpp>