const express = require('express');
const router = express.Router();
const sdk = require('./sdk.js');

  router.get('/setWallet', function(req, res){
    const ID = req.body.ID;
    const PID = req.body.PID;
    const PK = req.body.PK;
    const INFO = req.body.INFO;
    const LOCATION = req.body.LOCATION;
		const STATUS = req.body.STATUS;
    let args = [ID,PID,PK,INFO,LOCATION,STATUS];
    sdk.send(true, 'setWallet', args, res);
  });

  router.get('/getAllWallet', function (req, res) {
    let args = [];
    sdk.send(false, 'getAllWallet',args, res);
  });

  router.get('/setRentRecord', function (req, res) {
    const CID = req.body.CID;
    const H1CODE = req.body.H1CODE;
    let args = [CID,H1CODE];
    sdk.send(true, 'setRentRecord', args, res);
  });

  router.get('/getRentRecord', function (req, res) {
    const TID = req.body.TID;
    let args = [TID];
    sdk.send(true, 'getRentRecord', args, res);
  });

module.exports = router;