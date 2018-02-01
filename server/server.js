// Websocket initialization
var WebSocketServer = require("ws").Server
var wss = new WebSocketServer({
    port: 64000
});
var wsocket;
// Init banner to make it friendly

console.log('\nRCS10 Remote v0.1 - 2014 Juan J. Lamas EA1NK\n\n     ++++ Server  Up & Running ++++\n');
console.log("       Listening on port: 64000\n");
console.log("     ++++++++++++++++++++++++++++++\n");

//Websocket Callbacks
wss.on('connection', function (ws) {
    wsocket = ws;
    console.log('Client connected');

    wsocket.on('message', function (message) {

        procesa_comando(message);

    });

});

function procesa_comando(comando){

	var accion = comando.substr(0,3);
	if(accion == 'ant'){sel_antena(comando);}
	if(accion == 'sts'){read_status();}

}

function sel_antena(position){

	var exec = require('child_process').exec;
	var response = "";
	function puts(error,stdout,stderr){
		console.log(stdout);
		wsocket.send(stdout);
	}
	var posicion = position.substr(3,1);
	console.log("Switching to: " + posicion);
	wsocket.send("R:"+posicion);
	var exe = "relay_control -r" + posicion;
	//console.log(exe);
	exec(exe,puts);
	
}

function read_status(){

	// Get Relay Status
	var exec = require('child_process').exec;
	
	function puts(error,stdout,stderr){
		console.log("Board Status:"+stdout);
		wsocket.send(stdout);
		;}
	var exe = "relay_control -rs";
	exec(exe,puts);	
}
