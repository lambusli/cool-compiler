(*
    All inspirations come from /examples/list.cl
    I have no idea why we have to write two "entangled" classes
*)

(*
    * The class Stack keeps track of all the integers or symbols that have been pushed.
    * The Stack has the following operations:
    *   size() : the number of elements the stack contains.
    *   top() : the top element.
    *   push() : push a new element onto the top. Return the pushed element itself.
    *   pop() : remove the top element. Return the popped element itself.
*)
class Stack {
    size(): Int {0};

    top() : String {"You are on the stack bottom. "};

    pop() : Stack {
        -- If we are at the stack bottom, there is nothing to be popped. Thus, return self.
        self
    };

    push(s : String) : Stack {   -- Why SELF_TYPE wouldn't work?
        (new Cons).init(s, size() + 1, self)
    };
};

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
};



class Main inherits IO {
    myStack : Stack;

    main() : Object {{
        myStack <- (new Stack).push("a").push("b");
        out_string(myStack.top()).out_string("\n");
        out_int(myStack.size()).out_string("\n");
        myStack <- myStack.pop();
        out_string(myStack.top()).out_string("\n");
        out_int(myStack.size()).out_string("\n");
        myStack <- myStack.pop();
        out_string(myStack.top()).out_string("\n");
        out_int(myStack.size()).out_string("\n");
        myStack <- myStack.pop();
        out_string(myStack.top()).out_string("\n");
        out_int(myStack.size()).out_string("\n");
    }};
};
