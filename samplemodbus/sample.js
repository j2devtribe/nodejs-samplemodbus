var modbus = require('ModbusRtuMaster');
var rtu = new modbus("com4", 9600, 10, 100);
var monitor = { ad0:0,led0:false,led1:false,switch0:false }

rtu.addBitMonitor(1, 0x1000, 8);
rtu.addWordMonitor(1, 0x7000, 10);

rtu.on('valuechanged', function () {
    monitor.ad0 = rtu.Words[1][0x7000];
	
    monitor.led0 = rtu.Bits[1][0x1000];
    monitor.led1 = rtu.Bits[1][0x1001];
    monitor.switch0 = rtu.Bits[1][0x1002];
});


var express     = require('express');
var app         = express();
var bodyParser = require('body-parser');
var multer = require('multer'); 

app.use(bodyParser.json()); 
app.use(bodyParser.urlencoded({ extended: true })); 
app.use(multer()); 
app.use(express.static(__dirname+'/public'));

app.all('/monitor', function(req,res){
	res.json(monitor);
});

app.post('/control', function(req,res){
	rtu.setBit(1,0x1001,req.body.led1==1)
	res.json(monitor);
});
    
app.listen(3000);
