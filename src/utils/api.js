import axios from 'axios'
import { Message } from 'element-ui'
import router from '../router'

//请求拦截器--给请求封装token
axios.interceptors.request.use(config => {
  // 如果存在token，之后的请求都携带token
  const tokenStr = window.sessionStorage.getItem('tokenStr');
  if ( tokenStr ){
    config.headers['Authorization'] = tokenStr;
  }
  return config;
}, error => {
  console.log(error);
})


//响应拦截器--统一去处理错误
axios.interceptors.response.use(success => {    //这个success只代表成功访问到了这个接口，后端有可能返回操作不可行的错误代码
  //业务逻辑错误
  if ( success.status && success.status == 200 ){
    //data 有三部分，1）code 响应码；2）message 响应信息；3）object 有可能会携带对象(数据)
    // 所有错误的情况
    if ( success.data.code==500         // 业务逻辑错误
       || success.data.code==401        // 未登录
       || success.data.code==403){      // 权限禁止
        Message.error({message: success.data.message});
        return ;
    }
    // 成功直接输出message
    if ( success.data.message ){
      Message.success({message: success.data.message});
    }
    return success.data;  // 继续传递对象
  }
}, error => {     //完全错误，接口都没访问到，也就没有后端返回的JSON对象。所以使用response.code来判断
  if ( error.response.code==504                     //服务器有问题
    || error.response.code==404){                   //Not Found  
      Message.error({message: '服务器被吃了( ╯□╰ )'});
  } else if ( error.response.code==403 ){
    Message.error({message: '权限不足，请联系管理员！'});
  } else if ( error.response.code==401 ){
    Message.error({message: '尚未登录，请先登录！'});
    router.replace('/')
  } else {
    if ( error.response.data.message ){
      Message.error({message: error.response.data.message});
    } else {
      Message.error({message:'未知错误！'});
    }
  }
  return ;
});

let base = '';      //方便后续增加前置路径

//传送json格式的post请求
export const postRequest = (url, params)=>{
  return axios({
    method: 'post',
    url: `${base}${url}`,
    data: params
  })
}

//传送json格式的put请求
export const putRequest = (url, params)=>{
  return axios({
    method: 'put',
    url: `${base}${url}`,
    data: params
  })
}

//传送json格式的get请求
export const getRequest = (url, params)=>{
  return axios({
    method: 'get',
    url: `${base}${url}`,
    data: params
  })
}

//传送json格式的delete请求
export const deleteRequest = (url, params)=>{
  return axios({
    method: 'delete',
    url: `${base}${url}`,
    data: params
  })
}
