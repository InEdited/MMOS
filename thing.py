import subprocess as sp 
from flask import (
    Flask,
    request,
    render_template
)
command = ["./MMOS.exe"]
app = Flask(__name__)

names = ["FIFO","LRU","LFU","SCA","ESCA","Optimal"]
result = {"0":"0"}

@app.route('/')
def thing():
   return render_template('/index.html')

@app.route('/result',methods = ['POST', 'GET'])
def getResult():
   if request.method == 'POST':
      #result = request.form
      command.append(str(request.form.get('length')))
      command.append(str(request.form.get('number')))
      out = sp.check_output(command)
      out = out.decode('ascii', 'ignore').split()
      print(out)
      result = dict(zip(names, out))
      return render_template("result.html",result = result)

#out = sp.check_output(command)
#out.decode('ascii', 'ignore').split()

if __name__ == '__main__':
   app.run(debug = True)