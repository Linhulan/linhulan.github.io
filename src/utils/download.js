import axios from 'axios'

const service = axios.create({
  responseType: 'arraybuffer'
})

service.interceptors.request.use(config => {
  config.headers['Authorization'] = window.sessionStorage.getItem('tokenStr');
  return config;
}, error => {
  console.log(error);
})

service.interceptors.response.use(resp =>{
  let headers = resp.headers;
  let fileDownload = require('js-file-download');
  // content-disposition: attachment;filename=employee.xls
  // let fileName = headers['content-Disposition'].split(';')[1].split('filename=')[1];
  let fileName = headers['content-disposition'].split(';')[1].split('filename=')[1];
  let contentType = headers['content-type'];
  fileName = decodeURIComponent(fileName);
  fileDownload(resp.data, fileName, contentType);
})

let base = '';
export const downloadRequest = (url, params) => {
    return service({
        method: 'get',
        url: `${base}${url}`,
        data: params
    })
}


export default service;
