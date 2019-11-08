class Queen {
    xq1 : Int <- (new SELF_TYPE);
    xq2 : Int <- (new A);
};

class King inherits Queen {
    xk1 : Int <- (new SELF_TYPE);
};

class AA {
    x : Bool <- true;
};

class BB {
    y : Int <- 10;
};

class CC {
    z : String <- "here";
};

class DD {
    temp : Int;
    x : Int <- (temp <- 5);
    tempK : King;
    tempQ : Queen;
    xp : Int <- (tempQ <- tempK); -- You cannot assign sth superior to sth inferior
    xp2 : Int <- (tempQ <- new King);
};
