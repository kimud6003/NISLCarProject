import React, {useState,useEffect,useContext} from 'react';
import UserContext from '../context/User.context';
import { Form, Input, Button, Checkbox,List,Avatar } from 'antd';
import Password from 'antd/lib/input/Password';

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
const data = [
  {
    title: 'ghdk1103',
  },
  {
    title: 'abcef3333',
  },
  {
    title: 'Ane10230',
  },
  {
    title: 'Ane4',
  },
];

const user = () => {
  const [state, setstate] = useState('');
  const User = useContext(UserContext);

  useEffect(() => {
    const socket = socketIOClient(ENDPOINT);
    socket.on("connect", data => {
      socket.emit('auth',{uid:"user1"});
    });
  }, []);

  const onFinish = (values) => {
    console.log('Success:', values);
    User.id = values.username;
    User.pw = values.password;
    User.isLoggedIn = true;
  };

  const onFinishFailed = (errorInfo) => {
    console.log('Failed:', errorInfo);
  };

  return (
    <>
    <Form
      {...layout}
      name="basic"
      initialValues={{
        remember: true,
      }}
      onFinish={onFinish}
      onFinishFailed={onFinishFailed}
      style={{flexGrow:1}}
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
   <List
      style={{margin:"5%",flex:"1 1 40%"}}
      itemLayout="horizontal"
      dataSource={data}
      renderItem={item => (
        <List.Item>
          <List.Item.Meta
            avatar={<Avatar src="https://zos.alipayobjects.com/rmsportal/ODTLcjxAfvqbxHnVXCYX.png" />}
            title={<a href="https://ant.design">{item.title}</a>}
            description="Info:벤츠 3040-가, 위치: 동구 주차장 "
          />
        </List.Item>
      )}
    />
    </>

  );
};

export default user;
