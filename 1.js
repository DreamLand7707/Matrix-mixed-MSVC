function fun1() {
    var para = document.getElementById("demo");
    let pro = new Promise(function (resolve, reject) {
        if (document.getElementById("input").value == "hello") resolve("123");
        else reject("rejec");
    });
    pro.then(
        function (data) {
            para.innerHTML = data;
        },
        function (err) {
            para.innerHTML = err;
        }
    );
}
