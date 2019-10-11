class A {
};

Class BB__ inherits A {
};


class Premitive {y : String <- 3;};
class Lambus {y : String <- (3 + (5 - 3 * 4) / 6);};
class Lambus {y : String <- (isvoid 5);};
class C3 {y: String <- (new Life);};
class C4 {y: String <- (while 5 loop 6 pool);};
class C5 {y: String <- (if 1 then 2 else 3 fi);};
class C6 {y: String <- (y <- 3);};
-- class C7 {y: String <- (Y <- 3);};

class Testbranch {
    y : String <- (
        case (5) of
            v1 : Premitive => (y < 3);
            v2 : Lambus => (flag = true);
        esac
    );
};



class Testblock {
    y : String <- (
        {
            a = 5;
            b = 7;
            c < d + b * f * g + e;
            d <= not ( 1 + ~ self @ A . bar() * ( 2 - 3 / 4 ) <= 5 ) = ( 6 < 7 );
        }
    );
};



class Testselfdispatch {
    y : String <- (
        {
            func1(y < 3, a = 4, k = 5);
            func2();
            func3(5);
            (y * 4).func4(flag + true, glaf - false);
            (new Lambus)@Test.func5(x = 5, y = 6, z <= 7);
        }
    );
};




class TestLet {
    y : String <- (
        {
            let v1 : T1 <- 5, v2 : T2 in (i = true);
        }
    );
};



class TestFeature {
    y : String;
    func1() : Int {v1 = 1};
    func2(a : Int, c : Bool) : Bool {{v2 = 2; v3 = 3;}};
};



class TestPrec {
    y : String <- (
        {
            d <- not ( 1 + ~ self @ A . bar() * ( 2 - 3 / 4 ) <= 5 ) = ( 6 < 7 );
            (let a : INT in a) = true;
        }
    );
};

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
    *  CS433
    *
    *  Implementation of a simple stack machine.
    *
    *  Skeleton file
*)

(*
    All inspirations come from /examples/list.cl
    I have no idea why we have to write "entangled" subclasses
*)



(*
   The class A2I_adv provides more functions needed, in order to perform string to integer conversion.
*)
class A2I_adv inherits A2I {

    flag : Int <- 0;

    -- Check the a character and tell whether it is a digit.
    chr_is_num(s : String) : Bool {
       if s.substr(0, 1) = "0" then true else
       if s.substr(0, 1) = "1" then true else
       if s.substr(0, 1) = "2" then true else
       if s.substr(0, 1) = "3" then true else
       if s.substr(0, 1) = "4" then true else
       if s.substr(0, 1) = "5" then true else
       if s.substr(0, 1) = "6" then true else
       if s.substr(0, 1) = "7" then true else
       if s.substr(0, 1) = "8" then true else
       if s.substr(0, 1) = "9" then true else false
       fi fi fi fi fi fi fi fi fi fi
    };

    -- Check whether a string is a number
    str_is_num(s : String) : Bool {{
        flag <- 0;

        (let j : Int <- s.length() in
            (let i : Int <- 0 in
                while i < j loop {
                    if chr_is_num(s.substr(i, 1)) = false then flag <- flag + 1
                    else flag <- flag fi;
                    i <- i + 1;
                } pool
            )
        );

        if flag = 0 then true else false fi;
    }};
};



(*
    * The class Stack keeps track of all the integers or symbols that have been pushed.
    * The Stack has the following operations:
    *   size() : the number of elements the stack contains.
    *   top() : the top element.
    *   push() : push a new element onto the top. Return the pushed element itself.
    *   pop() : remove the top element. Return the popped element itself.
    *   eval() : do the required operations as stated in PA1.
    *   display() : display all elements in the stack.
*)


(*
    * The parent class
*)
class Stack inherits IO {
    size(): Int {0};

    top() : String {"You are on the stack bottom. "};

    pop() : Stack {
        -- If the stack is empty, there is nothing to be popped. Thus, return self.
        self
    };

    push(s : String) : Stack {   -- Why SELF_TYPE wouldn't work?
        (new Cons).init(s, size() + 1, self)
    };

    eval() : Stack {{
        if top() = "+" then (new Cons_plus).pop_then_plus(self)
        else if top() = "s" then (new Cons_swap).pop_then_swap(self)
        else if (new A2I_adv).str_is_num(top()) = true then self
        else if size() = 0 then self
        else {abort(); self;}
        fi fi fi fi;
    }};

    display() : Object {
        out_string("")
    };
};


(*
    * Subclass 1: Cons
    * Take care of size(), top(), pop(), and push()
*)
class Cons inherits Stack {
    top : String;
    size : Int;
    next : Stack;

    size() : Int {size};

    top() : String {top};

    pop() : Stack {{
        size <- size - 1;
        next;
    }};

    init(s : String, new_size : Int, rest : Stack) : Stack {{
        top <- s;
        size <- new_size;
        next <- rest;
        self;
    }};

    display() : Object {{
        out_string(top()).out_string("\n");
        next.display();
    }};

};


(*
    * Subclass 2: Cons_plus
    * Take care of the "+" command: pop the top "+" and the top two numbers, add, and push
*)
class Cons_plus inherits Cons {
    x1 : Int;
    x2 : Int;

    pop_then_plus(curr : Stack) : Stack {{
        curr <- curr.pop();         -- pop the "+" sign on the top.

        -- If less than 2 elements are left, then the operation is illegal.

        if not curr.size() < 2 then {
            x1 <- (new A2I_adv).a2i(curr.top()); curr <- curr.pop();
            x2 <- (new A2I_adv).a2i(curr.top()); curr <- curr.pop();

            -- Push the new sum as string onto the top.
            curr <- curr.push((new A2I_adv).i2a(x1 + x2));

        } else abort() fi;
        curr;
    }};
};



(*
    * Subclass 3: Cons_swap
    * Take care of the "s" command in PA1: pop the top "s" sign and swap the top two numbers
*)
class Cons_swap inherits Cons {
    s1 : String;
    s2 : String;

    pop_then_swap(curr : Stack) : Stack {{
        curr <- curr.pop();      -- Pop the top "s"

        -- If less than 2 elements are left, then the operation is illegal.

        if not curr.size() < 2 then {
            s1 <- curr.top(); curr <- curr.pop();
            s2 <- curr.top(); curr <- curr.pop();
            curr <- curr.push(s1).push(s2);
        } else abort() fi;

        curr;
    }};
};


class Main inherits IO {
    read_str : String;
    myStack : Stack;
    running : Bool;

    main() : Object {{
        myStack <- (new Stack);
        running <- true;

        while running = true loop {
            out_string(">");
            read_str <- in_string();
            if read_str = "x" then running <- false
            else if read_str = "e" then myStack <- myStack.eval()
            else if read_str = "d" then myStack.display()
            else myStack <- myStack.push(read_str)
            fi fi fi;
        } pool;
    }};
};
