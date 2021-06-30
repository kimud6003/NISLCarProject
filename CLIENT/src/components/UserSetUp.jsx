import React,{Fragment, useContext, useState} from 'react';
import { Form, Input, Button, Checkbox,Divider,List,Typography } from 'antd';
import UserContext from '../context/User.context';
const exec = require('child_process').exec;
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


const UserSetUpPage= () => {
  const User = useContext(UserContext);
  const [count, setCount] = useState("");
  
  const UserSetup1= (values)=>{
    exec(`./Clib/UserSetup/userSetup1`,
      function callback(err, stdout, stderr){
        if (err){
          console.error(err);
          }else{
            let parsing = stdout.split("\n");
            User.id = values.username;
            User.pw = values.password;
            User.ski = parsing[0];
            User.ai = parsing[1];
            User.PKi = parsing[2];
            User.PKi_D = parsing[3];
            console.log(stdout);
            let data = {PKi : User.PKi, PKi_D : User.PKi_D , ID : values.username }
              fetch(`http://localhost:3000/users/userSetup`,{
                method:`post`,
                body : JSON.stringify(data),
                headers:{
                  'Content-Type': 'application/json'
                }
              }).then(res => res.json())
              .then(response => {
                console.log(`Success:`,{response});
                UserSetup3(response);
              }) 
              .catch(err=> console.error('Error:',err))
            }
          }
    )
  }
  const UserSetup3= (data)=>{
    User.PID = data.PID;
    User.Ri = data.Ri;
    User.zi = data.zi;
    exec(`./Clib/UserSetup/userSetup3 ${User.id} ${User.pw} ${User.ski} ${User.ai} ${User.PID} ${User.Ri} ${User.zi}`,
          function callback(err, stdout, stderr){
            if (err){
              console.error(err);
              return false;
            }else{
            let parsing = stdout.split("\n");
            User.Bi = parsing[0];
            User.Ci = parsing[1];
            User.Di = parsing[2];
            User.Ei = parsing[3];
            User.HPID = parsing[4];
            User.Ri = parsing[5];
            console.log(User);
            setCount(0);
            setCount(User);
            }
          }
    )
  }
  const onFinish = (values) => {
    UserSetup1(values);
  };

  const onFinishFailed = (errorInfo) => {
    console.log('Failed:', errorInfo);
  };

  return (
    <Fragment>
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
        label="Username"
        name="username"
        rules={[
          {
            required: true,
            message: 'Please input your username!',
          },
        ]}
      >
        <Input />
      </Form.Item>

      <Form.Item
        label="Password"
        name="password"
        rules={[
          {
            required: true,
            message: 'Please input your password!',
          },
        ]}
      >
        <Input.Password />
      </Form.Item>

      <Form.Item {...tailLayout}>
        <Button type="primary" htmlType="submit">
          Submit
        </Button>
      </Form.Item>
    </Form>

    <Divider orientation="center">Default Size</Divider>
    <div style={{marginLeft: "25%", width: "50%"}}>
    <List
      bordered
      dataSource={Object.keys(count).map(function(key){ return [String(key)," : ",count[key]]})}
      renderItem={item => (
        <List.Item>
          <Typography.Text mark></Typography.Text> {item}
        </List.Item>
      )}
    />
    </div>
    </Fragment>
  );
};

export default UserSetUpPage;
