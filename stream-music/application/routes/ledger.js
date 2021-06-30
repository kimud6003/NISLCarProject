const express = require('express');
const router = express.Router();
const sdk = require('../api/sdk.js');

  router.get('/getWallet', function (req, res) {
    const walletid = req.body.Walletid;
    let args = [walletid];
    sdk.send(false, 'getWallet', args, res);
  });

  router.get('/setWallet', function(req, res){
    const name = req.body.Name;
		const id = req.body.Id;
    let args = [name, id];
    sdk.send(true, 'setWallet', args, res);
  });

  router.get('/setCar', function (req, res) {
    const title = req.body.Title;
    const Owner = req.body.Owner;
    const Info = req.body.Info;
    const Price = req.body.Price;
    const walletid = req.body.Walletid;
    let args = [title, Owner, Info,Price, walletid];
    sdk.send(true, 'setCar', args, res);
  });

  router.get('/getAllCar', function (req, res) {
    let args = [];
    sdk.send(false, 'getAllCar', args, res);
  });

  router.get('/purchaseCar', function (req, res) {
    const walletid = req.body.Walletid;
    const Carkey = req.body.Carkey;
    let args = [walletid, Carkey];
    sdk.send(true, 'purchaseCar', args, res);
});

module.exports = router;