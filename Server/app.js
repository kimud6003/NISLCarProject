const createError = require('http-errors');
const express = require('express');
const cors = require('cors');
const path = require('path');
const http = require('http');
const cookieParser = require('cookie-parser');
const logger = require('morgan');
var Single = require('./SingleTone');
var exec = require('child_process').exec;
const port = 3000;

const indexRouter = require('./routes/index');
const usersRouter = require('./routes/users');
const app = express();

app.use(cors());
app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);

app.use(function(req, res, next) {
  next(createError(404));
});

app.use(function(err, req, res, next) {
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};
  res.status(err.status || 500);
  res.render('error');
});

const httpserver = http.createServer({},app);

const io = require('socket.io')(httpserver,{
  cors:{
    origin: '*',
  }
});

var clients = [];

io.on(`connect`,function(socket){
  console.log("connect" + socket.id);
  socket.on('login',(data)=>{
    console.log(socket.id);
    var clientInfo = new Object();
    clientInfo.uid = data.uid;
    clientInfo.id = socket.id;
    clients.push(clientInfo);
  })

  socket.on('Auth1',(data)=>{
    const msg = data.msg;
    Single.Value.Xi = msg.Xi;
    exec(`./Clib/AUTH/Auth2 ${msg.PID} ${msg.Xi} ${msg.Xi_D} ${msg.CPID} ${msg.AUTH} ${msg.T1} ${msg.request}  ${msg.PKi} ${msg.PKi_D}`,function callback(err,stdout,stderr){
    if(err){
      console.log(err);
    }
    console.log(`Auth2 complete`)
    console.log(clients);
    let parsing = stdout.split("\n");
    Single.Value.qs = parsing[6];
    let data = {uid : msg.uid ,QS : parsing[0],QS_D : parsing[1], SID : parsing[2], AUTH_S : parsing[3], T2 : parsing[4], SM1 : parsing[5]}
    for (var i=0; i < clients.length; i++) {
      console.log(clients[i].uid);
      if(clients[i].uid == msg.rcvId){
        console.log(clients[i].id);
        io.to(clients[i].id).emit("Auth2",data);
      };
    }
    })
  })
  socket.on('Auth4',(data)=>{
    const msg = data;
    console.log(msg);
    exec(`./Clib/AUTH/Auth4 ${Single.Value.Xi} ${Single.Value.qs} ${msg.Yj} ${msg.T3} ${msg.CM1} ${msg.CM2}  ${msg.CM3} ${msg.CM4} ${msg.CM5} ${msg.CM6}`,function callback(err,stdout,stderr){
    if(err){
      console.log(err);
    }
    let parsing = stdout.split("\n");
    let data = {sendid : msg.sendId , CM1 : parsing[0], CM2 : parsing[1], SM2 : parsing[2], SM3 : parsing[3], T3 : parsing[4], T4 : parsing[5], Yj : parsing[6]}
    console.log(data);
    for (var i=0; i < clients.length; i++) {
      if(clients[i].uid == msg.rcvId){
        console.log(clients[i].id);
        io.to(clients[i].id).emit("Auth5",data);
      };
    }
    })
  })

  socket.on('disconnect', () => {
    for (var i=0; i < clients.length; i++) {
      var client = clients[i];
      if (client.id == socket.id) {
          clients.splice(i, 1);
        break;
      }
    }
    console.log('user disconnected');
  });
})

httpserver.listen(port,()=>{console.log(`listening ${port}`)})