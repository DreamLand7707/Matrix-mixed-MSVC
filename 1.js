function fun1() {
    class A {
        constructor() {
            this.opo = 3.6;
        }
    }
    dd = new A();
    var b;
    if (dd.constructor == A) b = true;
    else b = false;
    document.getElementById("para1").innerHTML = b.toString();
}
