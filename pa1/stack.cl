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
        else {abort(); self;}
        fi fi fi;
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
