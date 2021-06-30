var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
var http = require('http');
const cors = require('cors')

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');
var ledgersRouter = require('./routes/ledger');

var app = express();

app.use(cors())
app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/ledgers', ledgersRouter);


app.use(function(req, res, next) {
  next(createError(404));
});

app.use(function(err, req, res, next) {
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};
  res.status(err.status || 500);
  res.render('error');
});


const server = http.createServer(app);
var io = require('socket.io')(server,{cors:{origin:"*",}});
io.on('connection', function(socket){
   
  console.log("a user connected");
  socket.broadcast.emit('hi');
   
  socket.on('UserToServer', function(msg){
      console.log(msg);
  });
   
  socket.on('chatMessage', function(msg){
      console.log('message: ' + msg);
      io.emit('chatMessage', msg);
  }); 

});

server.listen(3000,()=>{
  console.log('서버 실행 중!');
})

module.exports = app;
