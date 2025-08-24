// almost ADT (Abstract Data Type)
// In the .h file, I declare the struct and all of its interface functions
// In the .c file, I include the .h file and implement all its functions
// The main function can see the internal details (e.g., Complex a; a.Re is a valid operation)
// but it's still fine if the main promises not to access the internal details
// and uses only the interface functions
// it's useful because you can code faster especially if you need a single instance
// of the collection you can just declare the variables that compose your data structure
// as global static variables and avoid using structs all together
// the downside is that the functions will have a growing number of parameters

// first-class ADT (like OOP)
// In the .h file, I only declare an opaque pointer to the struct
// using typedef and the interface functions
// In the .c file, I include the .h file, declare the struct itself as it's implemented internally,
// and implement its functions
// The main function, including the .h file, only sees the interface functions
// This solution requires dynamic allocation
// The trick is that by declaring a pointer to an incomplete struct,
// the internal details are actually invisible, but the struct type is visible to the main

// Example of a almost ADT: complex
// Example of a first-class ADT: person

// WARNING: in the case of first-class ADT if you create any extra functions that 
// are not in the header file you must mark them as static because they should not be seen
// outside of the scope of the file and are used to implement the interface functions
// (example: a recursive function)

// note that the terms "almost" and "first-class" are not generally recognised it's a specific 
// distinction made here to learn about how C and memory works
// You will find just the term ADT which refers to the definition of first-class adt
// while the almost adt is just a workaround to code faster (or if you only need a single instance)
