import Vue from 'vue'
import Vuex from 'vuex'
import { getRequest } from "../utils/api";
import { Notification } from 'element-ui';
import SockJS from 'sockjs-client';
import Stomp from 'stompjs'

Vue.use(Vuex);

const now = new Date();

const store = new Vuex.Store({
  state: {
    routes: [],
    sessions: {},   //{"张三#李四", [MESSAGE...]}
    admins:[],
    currentAdmin: JSON.parse(window.sessionStorage.getItem('user')),
    currentSession: null,
    filterKey:'',
    stomp: null,
    notRead: {},
  },

  mutations: {
    initRoutes(state, data){
      state.routes = data;
    },
    changeCurrentSession (state,currentSession) {
			state.currentSession = currentSession;
      Vue.set(state.notRead, state.currentAdmin.username+'#'+state.currentSession.username, false);
		},
		addMessage (state,msg) {
			let mss = state.sessions[state.currentAdmin.username+'#'+msg.to];
      if (!mss){
        // state.sessions[state.currentAdmin.username+'#'+msg.to] = [];
        // 添加响应式属性
        Vue.set(state.sessions, state.currentAdmin.username+'#'+msg.to, [])
      }
      state.sessions[state.currentAdmin.username+'#'+msg.to].push({
				content:msg.content,
				date: new Date(),
				self: !msg.notSelf
			})
		},
    INIT_DATA (state) {
      //浏览器本地的历史聊天记录
      let data = localStorage.getItem('vue-chat-session');
      //console.log(data)
      if (data) {
        state.sessions = JSON.parse(data);
      }
    },
    INIT_ADMINS(state, data){
      state.admins = data;
    },
    INIT_ADMIN(state, admin){
      state.currentAdmin = admin;
    }
  },

  actions: {
    connect(context){
      const stomp = Stomp.over(new SockJS('/ws/ep'));
      let token = window.sessionStorage.getItem('tokenStr');

      console.log(stomp);
      console.log("token = "+token);

      if (stomp.connected) {
        console.log('断开连接...');
        stomp.disconnect();
      }
      
      stomp.connect({'Auth-Token': token}, success=>{
        context.state.stomp.subscribe('/user/queue/chat', msg=>{
          let receiveMsg = JSON.parse(msg.body);
          // 消息提示
          if( !context.state.currentSession 
              || receiveMsg.from != context.state.currentSession.username){
            Notification.info({
              title:'【' + receiveMsg.fromNickName +'】发来一条消息',
              message: receiveMsg.content.length>10  
                      ? receiveMsg.content.substr(0,10)+'...'
                      : receiveMsg.content,
              position: 'bottom-right'
            })
            // 未读消息，小红点提示
            Vue.set(context.state.notRead, context.state.currentAdmin.username+'#'+receiveMsg.from, true);
          }

          receiveMsg.notSelf = true;
          receiveMsg.to = receiveMsg.from;
          context.commit('addMessage', receiveMsg);
        })
      }, error=>{
        console.log(error);
      })

      context.state.stomp = stomp;
    },
    initData (context) {
      context.commit('INIT_DATA');
      getRequest('/chat/admin').then(resp=>{
        if(resp){
          context.commit('INIT_ADMINS', resp);
        }
      })
    }
  }
})

store.watch(function (state) {
  return state.sessions
},function (val) {
  console.log('CHANGE: ', val);
  localStorage.setItem('vue-chat-session', JSON.stringify(val));
},{
  deep:true/*这个貌似是开启watch监测的判断,官方说明也比较模糊*/
})


export default store;