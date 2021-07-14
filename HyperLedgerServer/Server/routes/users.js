var express = require('express');
var exec = require('child_process').exec;
var router = express.Router();

/* GET users listing. */
router.post('/UserSetup/', function(req, res, next) {
  let PKi = req.body.PKi;
  let PKi_D = req.body.PKi_D;
  let ID = req.body.ID;
  exec(`./Clib/UserSetup/userSetup2 ${PKi} ${PKi_D} ${ID}`,function callback(err,stdout,stderr){
    if(err){
      console.log(err);
    }
    let parsing = stdout.split("\n");
    let data = {PID : parsing[0],Ri : parsing[1], zi : parsing[2]}
    res.send(data);
  })
});

module.exports = router;
