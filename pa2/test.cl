(*
* Part I original skeleton
*)

(*
    Models one-dimensional cellular automaton on a circle of finite radius.

    Arrays are faked as Strings, with X's respresenting live cells, dots representing dead cells.
    No error checking is done
*)
class CellularAutomaton inherits IO {
    population_map : String;

    init(map : String) : SELF_TYPE {{
            population_map <- map;
            self;
    }};

    print() : SELF_TYPE {{
        out_string(population_map.concat("\n"));
        self;
    }};

    num_cells() : Int {
        population_map.length()
    };

    cell(position : Int) : String {
        population_map.substr(position, 1)
    };

    cell_left_neighbor(position : Int) : String {
        if position = 0 then
            cell(num_cells() - 1)
        else
            cell(position - 1)
        fi
    };

    cell_right_neighbor(position : Int) : String {
        if position = num_cells() - 1 then
            cell(0)
        else
            cell(position + 1)
        fi
    };

    (* A cell will live if exactly 1 of itself and it's immediate neighbors are alive *)
    cell_at_next_evolution(position : Int) : String {
        if ((
            (if cell(position) = "X" then 1 else 0 fi) +
            (if cell_left_neighbor(position) = "X" then 1 else 0 fi) +
            (if cell_right_neighbor(position) = "X" then 1 else 0 fi)
        ) = 1)
        then
            "X"
        else
            "."
        fi
    };

    evolve() : SELF_TYPE {
        (let position : Int in
        (let num : Int <- num_cells[] in
        (let temp : String in {
            while position < num loop {
                temp <- temp.concat(cell_at_next_evolution(position));
                position <- position + 1;
            } pool;
            population_map <- temp;
            self;
        }
        ) ) )
    };
};

class Main {
    cells : CellularAutomaton;

    main() : SELF_TYPE {{
        cells <- (new CellularAutomaton).init("         X         ");
        cells.print();
        (let countdown : Int <- 20 in
            while countdown > 0 loop
                {
                    cells.evolve();
                    cells.print();
                    countdown <- countdown - 1;

            pool
        );  (* end let countdown *)
        self;
    }};
};

(*
* Part II cool code for PA1
*)

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

(*
* Part III: my own test
*)
(*) dj*(s
)*)s
kje *)(**)
--here is
cLAsS
"abcde"
-- here *"" is (*)
28372873
"djkwj
kf"f
"djlkew\0djl;elj"
"\"\'\n\b\\\""
"\
djk" pool"
--!!!!! Found line number bug: forgot to increment gCurrLineNo when newline is escaped !!!!!
array[0] = 5;
s =  j | k \ l
s1:String<-"[Mom says, \"don't waste food]\""
if (Lambus_listens = True and Elsa-listens=False && Eli's_father_listens = true) then {{
    **)
}}
k = 5 - 4
k' = 5 -- 4
a_bcd = `~!@#$%^&*()-_=+`

if (a > b or not a >= b && a < b || a <= b) then {printf("%s\n", "eat myself\!")}


s_big_mac :String <- "This is a super long string don't you even mess with it \n \t \f \b \i \- \r \v  This is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \vThis is a super long string don't you even mess with it \n \t \f \b \i \- \r \v"

short_weird :String <- "~!@#$%^&*()_+`=|}{[]'\'}`\?"

-- Fake Ternary operators
a > b ? a < b

\n\v\k\r\t \n \v \k \r \t \' \"I'm a prank"

xInt : Int <- 2938923842738718748317864731496

classelseiffi <- 5 is true

Hey! you forgot to start a comment! *)
(* Now you are good. `~!@#$%^&*()_=+\][|}{
May the force be with you... or not. You forgot to close it)
