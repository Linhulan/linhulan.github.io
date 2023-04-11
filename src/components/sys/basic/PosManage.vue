<template>
  <div>
    <div>
      <el-input
        size="small"
        class="addPosInput"
        placeholder="添加职位"
        suffix-icon="el-icon-plus"
        v-model="pos.name"
        @keydown.enter.native="addPosition"
      >
      </el-input>
      <el-button
        size="small"
        icon="el-icon-plus"
        type="primary"
        @click="addPosition"
        >添加</el-button
      >
    </div>
    <div class="posManageMain">
      <el-table
        :data="positions"
        style="width: 70%"
        stripe
        border
        size="small"
        @selection-change="handleSelectionChange"
      >
        <el-table-column type="selection" width="55"> </el-table-column>
        <el-table-column prop="id" label="编号" width="55"> </el-table-column>
        <el-table-column prop="name" label="职位" width="120">
          <template slot-scope="scope">
            <div slot="reference" class="name-wrapper">
              <el-tag size="medium">{{ scope.row.name }}</el-tag>
            </div>
          </template>
        </el-table-column>
        <el-table-column prop="createDate" label="创建时间" width="120">
        </el-table-column>
        <el-table-column prop="enabled" label="是否启用" width="120">
        </el-table-column>
        <el-table-column label="操作">
          <template slot-scope="scope">
            <el-button
              size="small"
              @click="showEditView(scope.$index, scope.row)"
              >编辑</el-button
            >
            <el-button
              size="small"
              type="danger"
              @click="handleDelete(scope.$index, scope.row)"
              >删除</el-button
            >
          </template>
        </el-table-column>
      </el-table>
    </div>
    <el-button
      type="danger"
      size="small"
      style="margin-top: 8px"
      :disabled="this.multipleSelection.length == 0"
      @click="deleteMany"
      >批量删除</el-button
    >
    <el-dialog title="编辑职位" :visible.sync="dialogVisible" width="30%">
      <div>
        <el-tag>职位名称</el-tag>
        <el-input
          v-model="updatePos.name"
          class="updateInput"
          size="small"
        ></el-input>
      </div>
      <span slot="footer" class="dialog-footer">
        <el-button size="small" @click="dialogVisible = false">取 消</el-button>
        <el-button size="small" type="primary" @click="doUpdate"
          >确 定</el-button
        >
      </span>
    </el-dialog>
  </div>
</template>

<script>
export default {
  name: "PosManage",
  data() {
    return {
      pos: {
        name: "",
      },
      updatePos: {
        name: "",
      },
      positions: [],
      dialogVisible: false,
      multipleSelection: [],
    };
  },
  methods: {
    addPosition() {
      if (this.pos.name) {
        this.postRequest("/system/basic/pos", this.pos).then((resp) => {
          if (resp) {
            this.initPositions();
            this.pos.name = "";
          }
        });
      } else {
        this.$message.error("职位名称不能为空！");
      }
    },

    showEditView(index, data) {
      Object.assign(this.updatePos, data); //浅拷贝，防止双向绑定后修改name直接显示在页面上
      // this.updatePos = data;
      this.updatePos.createDate = ""; //后端自动生成，不接受修改
      this.dialogVisible = true;
    },
    doUpdate() {
      this.putRequest("/system/basic/pos/", this.updatePos).then((resp) => {
        if (resp) {
          this.dialogVisible = false;
          this.initPositions();
        }
      });
    },

    handleDelete(index, data) {
      this.$confirm(
        "此操作将永久删除[" + data.name + "]职位, 是否继续?",
        "提示",
        {
          confirmButtonText: "确定",
          cancelButtonText: "取消",
          type: "warning",
        }
      ).then(() => {
          this.deleteRequest("/system/basic/pos/" + data.id).then((resp) => {
            if (resp) {
              this.initPositions();
            }
          });
        })
        .catch(() => {
          this.$message({
            type: "info",
            message: "已取消删除",
          });
        });
    },
    handleSelectionChange(val) {
      this.multipleSelection = val;
    },
    deleteMany(){
      this.$confirm(
        "此操作将永久删除[" + this.multipleSelection.length + "]条职位, 是否继续?",
        "提示",
        {
          confirmButtonText: "确定",
          cancelButtonText: "取消",
          type: "warning",
        }
      )
      .then(() => {
        let ids = '?';
        this.multipleSelection.forEach(item=>{
          ids += 'ids='+item.id+'&';
        });
        this.deleteRequest("/system/basic/pos/" + ids).then((resp) => {
          if (resp) {
            this.initPositions();
          }
        }).catch(()=>{
            this.$message({
            type: "error",
            message: "参数错误",
          });
        })
      })
      .catch(() => {
        this.$message({
          type: "info",
          message: "已取消删除",
        });
      });
    },

    initPositions() {
      this.getRequest("/system/basic/pos/").then((resp) => {
        if (resp) {
          this.positions = resp;
        }
      });
    },
  },
  mounted() {
    this.initPositions();
  },
};
</script>

<style scoped>
.addPosInput {
  width: 300px;
  margin-right: 8px;
}
.posManageMain {
  margin-top: 10px;
}
.updateInput {
  width: 200px;
  margin-left: 8px;
}
</style>