import React, {useState,useEffect,useContext} from 'react';
import UserContext from '../context/User.context';
import socketIOClient from "socket.io-client";
import { Form, Input, Button, Checkbox } from 'antd';
import Password from 'antd/lib/input/Password';
const exec = require('child_process').exec;
const ENDPOINT = "http://localhost:3000";

const layout = {
  labelCol: {
    span: 8,
  },
  wrapperCol: {
    span: 16,
  },
};
const tailLayout = {
  wrapperCol: {
    offset: 8,
    span: 16,
  },
};

const AUTH= () => {
  let socket;
  const [state, setstate] = useState('');
  const User = useContext(UserContext);

  useEffect(() => {
    if(User.id != null){
      socket = socketIOClient(ENDPOINT);
      socket.on("connect", data => {
      socket.emit('login',{uid : User.id})
      console.log("연결 완료");
      })

      socket.on("Auth2",data => {
      console.log(data);
      exec(`./Clib/AUTH/Auth3 ${data.QS} ${data.QS_D} ${data.SID} ${data.AUTH_S} ${data.SM1} ${data.T2} `,
      function callback(err,stdout,stderr){
        if(err){
          console.error(err);
        }else{
            console.log("AUTH3 result : ");
            console.log(stdout);
            let parsing = stdout.split("\n");
            let msg = {sendId : User.sendId,rcvId : User.rcvId,Yj : parsing[0], Yj_D : parsing[1], CM1 : parsing[2], CM2 : parsing[3], CM3 : parsing[4], CM4 : parsing[5], CM5 : parsing[6], CM6 : parsing[7], T3 : parsing[8]}
            socket.emit('Auth4',msg);
        }
      })
    })
      socket.on("Auth5",data => {
        console.log(data);
        exec(`./Clib/AUTH/Auth5 ${User.xi} ${data.Yj} ${data.Yj_D}  ${data.CM1} ${data.CM2} ${data.SM2} ${data.SM3} ${data.T3} ${data.T4} `,
        function callback(err,stdout,stderr){
          if(err){
            console.error(err);
          }else{
            console.log("AUTH5 result : ");
            console.log(stdout);
            
          }
        })
      })
    };
  }, []);

 
  const onFinish = (values) => {
    exec(`./Clib/AUTH/Auth1 ${User.ski} ${User.id} ${User.pw} ${User.Bi} ${User.Ci} ${User.Di} ${User.Ei} ${User.HPID} 3430주10`,
      function callback(err, stdout, stderr){
        if (err){
          console.error(err);
          }else{
            console.log("AUTH1 result : ");
            console.log(stdout);
            let parsing = stdout.split("\n");
            User.Xi = parsing[0];
            User.Xi_D = parsing[1];
            User.CPID = parsing[2];
            User.AUTH = parsing[3];
            User.T1 = parsing[4];
            User.Reqst = parsing[5];
            User.xi = parsing[6];

// TODO SOCKET 통신 구간 
            User.sendId = User.id;
            User.rcvId = values.socketId;
            const msg = {sendId : User.sendId,rcvId : User.rcvId,Xi : User.Xi,Xi_D : User.Xi_D, CPID : User.CPID, AUTH : User.AUTH, T1 : User.T1, request : User.Reqst, PID : User.PID, PKi: User.PKi, PKi_D: User.PKi_D }

            socket.emit('Auth1',{msg});
          }
      }
    )

  };

  const onFinishFailed = (errorInfo) => {
    console.log('Failed:', errorInfo);
  };

  return (
  <Form
      {...layout}
      name="basic"
      initialValues={{
        remember: true,
      }}
      onFinish={onFinish}
      onFinishFailed={onFinishFailed}
      style={{flexGrow:0.7}}
    >
      <Form.Item
        label="Socket Name"
        name="socketId"
        rules={[
          {
            required: true,
            message: 'Please input your Socketname!',
          },
        ]}
      >
        <Input />
      </Form.Item>

      <Form.Item {...tailLayout}>
        <Button type="primary" htmlType="submit">
          요청하기 
        </Button>

        <Button type="primary" htmlType="submit" style={{marginLeft : "10px"}}>
          Submit
        </Button>
      </Form.Item>
    </Form>
  );
};

export default AUTH;



