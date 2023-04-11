<template>
  <div>
    <div style="width: 70%">
      <el-input
        placeholder="输入关键字进行过滤"
        v-model="filterText"
        prefix-icon="el-icon-search">
      </el-input>

      <el-tree
        class="filter-tree"
        :data="deps"
        :props="defaultProps"
        default-expand-all
        :filter-node-method="filterNode"
        :expand-on-click-node="false"
        ref="tree">
        <span class="custom-tree-node tree-row" slot-scope="{ node, data }">
          <span>{{ data.name }}</span>
          <span>
            <el-button
              type="text"
              size="mini"
              class="depBtn"
              @click="() => showAddView(data)"
            >
              添加部门
            </el-button>
            <el-button
              type="text"
              size="mini"
              class="depBtn"
              style="color: #ff0000"
              @click="() => remove(data)"
            >
              删除部门
            </el-button>
          </span>
        </span>
      </el-tree>
      <el-dialog
        title="添加部门"
        :visible.sync="dialogVisible"
        width="30%">
        <div>
          <table>
            <tr>
              <td>
                <el-tag>上级部门</el-tag>
              </td>
              <td>{{pname}}</td>
            </tr>
            <tr>
              <td>
                <el-tag>部门名称</el-tag>
              </td>
              <td>
                <el-input v-model="dep.name" placeholder="请输入部门名称"></el-input>
              </td>
            </tr>
          </table>
        </div>
        <span slot="footer" class="dialog-footer">
          <el-button @click="dialogVisible = false">取 消</el-button>
          <el-button type="primary" @click="doAddDep">确 定</el-button>
        </span>
      </el-dialog>
    </div>

    <div>

    </div>
  </div>
</template>

<script>
export default {
  name: 'DepManage',
  data() {
    return {
      filterText: '',
      dialogVisible: false,
      deps: [],
      defaultProps: {
        children: 'children',
        label: 'name'
      },
      dep: {
        name: '',
        parentId: -1
      },
      pname: ''
    }
  },
  methods: {
    filterNode(value, data) {
      if (!value) return true;
      return data.name.indexOf(value) !== -1;
    },
    initDep(){
      this.dep = {
        name: '',
        parentId: -1
      };
      this.pname = '';
    },
    initDeps(){
      this.getRequest('/system/basic/department/').then(resp=>{
        if ( resp ){
          this.deps = resp;
        }
      })
    },
    showAddView(data){
      this.dialogVisible = true;
      this.pname = data.name;
      this.dep.parentId = data.id;
    },
    doAddDep(){
      this.postRequest('/system/basic/department/', this.dep).then(resp=>{
        if ( resp ){
          this.dialogVisible = false;
          this.initDep();
          this.initDeps();
        }
      })
    },
    remove(data){
      if ( data.isParent ){
        this.$message.error('该部门还有子部门');
      } else {
        this.$confirm(
          "此操作将永久删除[" + data.name + "]部门, 是否继续?",
          "提示",
          {
            confirmButtonText: "确定",
            cancelButtonText: "取消",
            type: "warning",
          }
        )
          .then(() => {
            this.deleteRequest('/system/basic/department/'+data.id).then((resp) => {
                if (resp) {
                  this.initDeps();
                }
              });
          })
          .catch(() => {
            this.$message({
              type: "info",
              message: "已取消删除",
            });
          });
      }
      
    },
  },
  watch: {
    filterText(val) {
      this.$refs.tree.filter(val);
    }
  },
  mounted(){
    this.initDeps();
  }
}
</script>

<style scoped>
.depBtn{
  padding: 3px;
  margin: 0px 0px 0px 6px;
}
.tree-row{
  display:flex;
  justify-content: space-between;
  width: 100%;
}
</style>