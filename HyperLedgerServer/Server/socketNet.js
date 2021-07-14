io.on(`connect`,function(socket){
  socket.on('login',(data)=>{
    console.log(data.uid);
  })

  socket.on('Auth1',(data)=>{
    const msg = data.msg;
    exec(`./Clib/AUTH/Auth2 ${msg.PID} ${msg.Xi} ${msg.Xi_D} ${msg.CPID} ${msg.AUTH} ${msg.T1} ${msg.request}  ${msg.PKi} ${msg.PKi_D}`,function callback(err,stdout,stderr){
    if(err){
      console.log(err);
    }
      // console.log(data);
      console.log(stdout);
      // console.log(data.msg.rcvId);
      // console.log(data.msg.sendId);
    let parsing = stdout.split("\n");
    let data = {uid : msg.uid ,QS : parsing[0],QS_D : parsing[1], SID : parsing[2], AUTH_S : parsing[3], T2 : parsing[4], SM1 : parsing[5]}
    socket.emit(`Auth2`,function(data){
      for(var i = 0; i < )
    });
    })
  })
  socket.on('disconnect', () => console.log(`Connection left (${socket.id})`));
})