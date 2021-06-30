import React, {useState,useEffect,useContext} from 'react';
import UserContext from '../context/User.context';
import { Layout, Menu, Breadcrumb } from 'antd';
import 'antd/dist/antd.css';
import {
  UserOutlined,
  UserSwitchOutlined,
  UserAddOutlined,
  CarOutlined
} from '@ant-design/icons';
import UserSetUpPage from './UserSetUp'
import AuthPage from './AUTH'
import OwnerSetUpPage from './OwnerSetUp'
import Userview from './user'
import OwnerSetUp from './OwnerSetUp';

const { Header, Content, Footer, Sider } = Layout;
const { SubMenu } = Menu;
const SiderView = ()=>{
  let show = null;
  const User = useContext(UserContext);
  const [state, setstate] = useState({
    select:1,
  })
const chooseSelect = (key)=>{
      setstate({
        select:key
      })
  }
    if(state.select===1) {
        show=<UserSetUpPage/>
      }else if (state.select===2){
        show=<OwnerSetUpPage/>
      }else if (state.select===3){
        show=<AuthPage/>
      }else if (state.select===4){
        if (User.isLoggedIn===true)
        show=<Userview/>
      }
    return (
      <Layout style={{ minHeight: '100vh' }}>
        <Sider>
          <div className="logo" />
          <Menu theme="dark" defaultSelectedKeys={['1']} mode="inline">
            <Menu.Item key="1" icon={<UserAddOutlined />} onClick={()=>chooseSelect(1)}>
              UserSetUp 
            </Menu.Item>
            <Menu.Item key="2" icon={<UserSwitchOutlined />} onClick={()=>chooseSelect(2)}>
              OwnerSetUp 
            </Menu.Item>
            <Menu.Item key="3" icon={<UserSwitchOutlined />} onClick={()=>chooseSelect(3)}>
              Auth
            </Menu.Item>
            <Menu.Item key="4" icon={<UserSwitchOutlined />} onClick={()=>chooseSelect(4)}>
              Owner
            </Menu.Item>
          </Menu>
        </Sider>
        <Layout className="site-layout">
          <Header className="site-layout-background" style={{ padding: 0, color:"white",textAlign:"center",fontSize:"2rem"}} >Smart Car</Header>
          <Content style={{ }}>
            <div className="site-layout-background" style={{ padding: 24, minHeight: 360,display:"flex",flexWrap:"wrap", justifyContent:"flex-start",alignItems:"center"}}>
              {show}
            </div>
          </Content>
          <Footer style={{ textAlign: 'center' }}></Footer>
        </Layout>
      </Layout>
    );
}

export default SiderView;
