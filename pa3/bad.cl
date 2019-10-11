
(*
 *  Execute "coolc bad.cl" to see the error messages that the coolc parser
 *  generates
 *)

(* error in blocks*)
class ErrBlock {
    y : String <- (
        {
            Notanexpression;
            (unclosedParenthesis;
            while true loop unclosedLoop ;
            while true unclosedLoop pool;
            I have had it with these monkey-fighting snakes on this Monday-to-Friday plane;
            {;
            if true then noElse;
            if true noThen else false;
            < lackoperand;
            lackoperand =;
            malfunc(;
            typeInDispatch(x : Int);
            malStatic@.func(snake);
            badAssign < - badAssign;
            BadAssign < - BadAssign;
            case true of badcase esac;
            case true forgetOf : Int => true esac;
            case true forgetOf : Int => true esac;
        }
    );
};



(* error in feature list *)
class ErrFea {
    y <- String;
    y : String <- Lambus;
    func1(a = b) : Lambus {true};
    func2(a : Int) {true};
    func3(s : String) : Lambus {;
    funcCorrect(s : String, t : Int) : Lambus {true};
    true ;
    {;
};


(* error:  b is not a type identifier *)
Class b inherits A {
};

(* error:  a is not a type identifier *)
Class C inherits a {
};

(* error:  keyword inherits is misspelled *)
Class D inherts A {
};

(* error:  closing brace is missing *)
--Class E inherits A {
;

class F inherit A {};

(* no error *)
class A {
};

class ErrLet {
    y : String <- (
        {
            let v0: nt, v1 : nt, v2 : Int in (true);
            let v1 : nt in (let v2 : nt, v3 : Int in (v1 + v2 * v3)); 
            Notanexpression;
        }
    );
};
