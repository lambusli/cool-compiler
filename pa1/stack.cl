(*
 *  CS433
 *
 *  Implementation of a simple stack machine.
 *
 *  Skeleton file
 *)

 (*
     The class A2I provides integer-to-string and string-to-integer
     conversion routines. To use these routines, either inherit them
     in the class where needed, have a dummy variable bound to
     something of type A2I, or simply write (new A2I).method(argument).
 *)

 class A2I {
   (*
     c2i converts a 1-character string to an integer. Aborts
     if the string is not "0" through "9"
   *)
   c2i(char : String) : Int {
     if char = "0" then 0 else
     if char = "1" then 1 else
     if char = "2" then 2 else
     if char = "3" then 3 else
     if char = "4" then 4 else
     if char = "5" then 5 else
     if char = "6" then 6 else
     if char = "7" then 7 else
     if char = "8" then 8 else
     if char = "9" then 9 else
     { abort(); 0; }  -- the 0 is needed to satisfy the type checking
     fi fi fi fi fi fi fi fi fi fi
   };

   (*
     i2c is the inverse of c2i.
   *)
   i2c(i : Int) : String {
     if i = 0 then "0" else
     if i = 1 then "1" else
     if i = 2 then "2" else
     if i = 3 then "3" else
     if i = 4 then "4" else
     if i = 5 then "5" else
     if i = 6 then "6" else
     if i = 7 then "7" else
     if i = 8 then "8" else
     if i = 9 then "9" else
     { abort(); ""; }  -- the "" is needed to satisfy the typchecker
       fi fi fi fi fi fi fi fi fi fi
   };

   (*
     a2i converts an ASCII string into an integer. The empty string
     is converted to 0. Signed and unsigned strings are handled.  The
     method aborts if the string does not represent an integer. Very
     long strings of digits produce strange answers because of arithmetic
     overflow.
   *)
   a2i(s : String) : Int {
     if s.length() = 0 then 0 else
       if s.substr(0,1) = "-" then ~a2i_aux(s.substr(1, s.length()-1)) else
         if s.substr(0,1) = "+" then a2i_aux(s.substr(1, s.length()-1)) else
           a2i_aux(s)
     fi fi fi
   };

   (*
     a2i_aux converts the usigned portion of the string.  As a programming
     example, this method is written iteratively.
   *)
   a2i_aux(s : String) : Int {
     (let int : Int <- 0 in {
       (let j : Int <- s.length() in
         (let i : Int <- 0 in
           while i < j loop
             {
               int <- int * 10 + c2i(s.substr(i,1));
               i <- i + 1;
             }
           pool
         )
       );
       int;
     })
   };

   (*
     i2a converts an integer to a string.  Positive and negative
     numbers are handled correctly.
   *)
   i2a(i : Int) : String {
     if i = 0 then "0" else
       if 0 < i then i2a_aux(i) else
         "-".concat(i2a_aux(i * ~1))
     fi fi
   };

     (*
       i2a_aux is an example using recursion.
     *)
     i2a_aux(i : Int) : String {
       if i = 0 then "" else
 	      (let next : Int <- i / 10 in
 		      i2a_aux(next).concat(i2c(i - next * 10))
 	      )
       fi
     };

 };

 (*
    The class A2I_adv provides more functions needed, in order to perform string to integer conversion.
 *)
class A2I_adv inherits A2I {
    check_1st_char(s : String) : Int {
        if s.substr(0, 1) = "0" then 1 else
        if s.substr(0, 1) = "1" then 1 else
        if s.substr(0, 1) = "2" then 1 else
        if s.substr(0, 1) = "3" then 1 else
        if s.substr(0, 1) = "4" then 1 else
        if s.substr(0, 1) = "5" then 1 else
        if s.substr(0, 1) = "6" then 1 else
        if s.substr(0, 1) = "7" then 1 else
        if s.substr(0, 1) = "8" then 1 else
        if s.substr(0, 1) = "9" then 1 else 0
        fi fi fi fi fi fi fi fi fi fi
    };
};


class Main inherits IO {
    read_str : String;
    maybeNum : Int;
    x : Int;

    main() : Object {
        {
            read_str <- in_string();
            maybeNum <- (new A2I_adv).check_1st_char(read_str);
            if maybeNum = 1 then {
                x <- (new A2I_adv).a2i(read_str);
                out_int(x).out_string("\n");
            } else {
                out_string(read_str).out_string("\nThis is NOT a number\n");
            } fi;

        }
    };

};
