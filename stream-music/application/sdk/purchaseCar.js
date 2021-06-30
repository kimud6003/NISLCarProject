'use strict';

const { FileSystemWallet, Gateway } = require('fabric-network');
const path = require('path');
MS0
const ccpPath = path.resolve(__dirname, '..', 'connection.json');

async function main() {
    try {

        const walletid = process.argv[2];
        const key = process.argv[3];
        const user = process.argv[4];

        const walletPath = path.join(process.cwd(), '..', 'wallet');
        const wallet = new FileSystemWallet(walletPath);
        console.log(`Wallet path: ${walletPath}`);

        const userExists = await wallet.exists(user);
        if (!userExists) {
            console.log('An identity for the user "user1" does not exist in the wallet');
            console.log('Run the registUser.js application before retrying');
            return;
        }

        const gateway = new Gateway();
        await gateway.connect(ccpPath, { wallet, identity: user, discovery: { enabled: true, asLocalhost: true } });

        const network = await gateway.getNetwork('channelsales1');

        const contract = network.getContract('smartcar-cc');


        const result = await contract.submitTransaction('purchaseCar', walletid, key);
        console.log('Transaction has been submitted');

        await gateway.disconnect();

    } catch (error) {
        console.error(`Failed to submit transaction: ${error}`);
        process.exit(1);
    }
}

main();
