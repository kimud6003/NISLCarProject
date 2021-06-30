const express = require('express');
const router = express.Router();
const sdk = require('../api/sdk');
const regi = require('../sdk/regi')

/* GET users listing. */
router.get('/', function(req, res, next) {
  res.send('respond with a resource');
});

router.get('/registUsers', function (req, res) {
    const user = req.body.user
    regi(res,user);
});

router.get('/getWallet', function (req, res) {
    const walletid = req.body.walletid;
    const user = req.body.user
    let args = [walletid,user];
    sdk.send(false, 'getWallet', args, res, user);
});
router.get('/setCar', function (req, res) {
    const title = req.body.title;
    const singer = req.body.singer;
    const price = req.body.price;
    const walletid = req.body.walletid;
    const user = req.body.user

    let args = [title, singer, price, walletid,user];
    sdk.send(true, 'setCar', args, res, user );
});
router.get('/getAllCar', function (req, res) {
    let args = [];
    const user = req.body.user
    let args = [user];
    sdk.send(false, 'getAllCar', args, res, user);
});
router.get('/purchaseCar', function (req, res) {
    const walletid = req.body.walletid;
    const key = req.body.Carkey;
    const user = req.body.user
    let args = [walletid, key,user];
    sdk.send(true, 'purchaseCar', args, res,user);
});

module.exports = router;
