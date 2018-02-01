var host = 'your_host';
var port = 'your_port';
var socket = new WebSocket('ws://' + host + ":" + port);

socket.onopen = function () {

    console.log("Connected!");
    $("#connection_status").text("Connected");
    switchClasses("badge-dark", "badge-success", "connection_status");
    askStatus();
    var status_polling = setInterval(function () { askStatus(); }, 10000); //Ask status each 10 seconds.
}

socket.onerror = function (error) {

    $("#connection_status").text("ERROR");
    switchClasses("badge-dark", "badge-danger", "connection_status");

}

socket.onmessage = function (msg) {

    console.log("Received: " + msg.data);
    processMessage(msg);
}

socket.onclose = function () {

    console.log("Disconnected!");
    $("#connection_status").text("Disconnected");
    switchClasses("badge-danger", "badge-dark", "connection_status");
    switchClasses("badge-success", "badge-dark", "connection_status");
}

function switchAnt(port) {
    console.log("Switching to antenna:" + port);
    socket.send("ant" + port);
}

function askStatus() {

    socket.send('sts');
}

function processMessage(msg) {

    var data = msg.data;
    var pos = data.search("R:");
    if (pos == 0) { // Is response from our command
        var selected_antenna = data.split(":")[1];
        console.log("Selected Antenna:" + selected_antenna);
        return;
    } else { //Is response from our USB board application
        var selected_antenna = data.split(":")[1];
        var ant = parseInt(selected_antenna);
        ant = Math.log(ant) / Math.log(2);
        resetButtonClass()
        switchClasses('badge-dark', 'badge-success', 'btn_' + ant);

    }


}
function switchClasses(before, after, element) {

    $("#" + element).removeClass(before);
    $("#" + element).addClass(after);

}

function resetButtonClass() {

    $("#ant_ports").find('button').each(function () {

        $(this).removeClass();
        $(this).addClass('btn');

    });

}