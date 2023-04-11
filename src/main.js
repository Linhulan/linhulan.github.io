import Vue from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'
import ElementUI from 'element-ui'
import  'element-ui/lib/theme-chalk/index.css'
import 'font-awesome/css/font-awesome.css'


import { postRequest, putRequest, getRequest, deleteRequest } from './utils/api'
import { initMenu } from './utils/menus.js'
import { downloadRequest } from './utils/download'

Vue.use(ElementUI, {size:'small'});
Vue.config.productionTip = false

Vue.prototype.postRequest = postRequest;
Vue.prototype.putRequest = putRequest;
Vue.prototype.getRequest = getRequest;
Vue.prototype.deleteRequest = deleteRequest;
Vue.prototype.downloadRequest = downloadRequest;

router.beforeEach((to, from, next) => {
  if ( window.sessionStorage.getItem('tokenStr') ){
    initMenu(router, store);
    //判断用户信息是否存在
    if ( !window.sessionStorage.getItem('user') ){
      getRequest('/admin/info').then(resp => {
        if ( resp ){
          // 存入用户信息
          window.sessionStorage.setItem('user', JSON.stringify(resp));
          this.$store.commit('INIT_ADMIN', resp);
          next();
        }
      })
    }
    next();
  } else {
    if ( to.path=='/' ){
      next();
    } else {
      next('/?redirect='+to.path);
    }
  }

})

new Vue({
  router,
  store,
  render: h => h(App)
}).$mount('#app')
