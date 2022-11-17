import axios from 'axios';
const Axios = axios
Axios.defaults.headers.common['X-Requested-With'] = 'XMLHttpRequest';
Axios.defaults.withCredentials = true
export default Axios;
