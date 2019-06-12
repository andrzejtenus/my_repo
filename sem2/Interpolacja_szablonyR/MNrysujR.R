rysuj=function(leg='topright',blw=FALSE){
#leg - po³o¿enie legendy, NA - nie wykreœla legendy
#   "bottomright", "bottom", "bottomleft", "left", "topleft", 
#   "top", "topright", "right" lub "center"  
#blw - wykreœlenie b³êdu wzglêdnego 
# nale¿y ustawiæ w³aœciwy katalog roboczy
setwd("U:\\MN\\Interpolacja\\F\\Interpolacja_szablonyR")
# przyjêto nazy plików: 'wezlyA.rex' i 'wynA.rex'
wezly=read.table('we',header=T)
nwezly=colnames(wezly)
n=length(wezly[[1]])-1
dx=diff(wezly[[1]])
opt=ifelse(abs(dx[1]-dx[2])<1e-5,0,1)
#browser()
wyn=read.table('w',header=TRUE)
nwyn=colnames(wyn)
nn=ifelse(blw,5,4)
xxlim=c(min(wyn[[1]]),max(wyn[[1]]))
maxblb=max(abs(wyn[[4]]))
color=c('black','blue','red','green','magenta')
yylim=c(min(unlist(wyn[2:nn])),max(unlist(wyn[2:nn])))
plot(wezly[[1]],wezly[[2]],xlim=xxlim,ylim=yylim,xlab='',ylab='',col=color[1])
grid()
lines(wyn[[1]],wyn[[2]],col=color[2])
lines(wyn[[1]],wyn[[3]],col=color[3])
lines(wyn[[1]],wyn[[4]],col=color[4])
if (blw) {
  lines(wyn[[1]],wyn[[5]],col=color[5])
  maxblw=max(abs(wyn[[5]]))
  title(sub=paste('n=',n,',  opt=',opt,',   maxblb=',format(maxblb,digits=3),',   maxblw=',format(maxblw,digits=3)),xlab=nwyn[1])
}else
  title(sub=paste('n=',n,',  opt=',opt,',   maxblb=',format(maxblb,digits=3)),xlab=nwyn[1])
legend(leg,legend=c(nwezly[2],nwyn[2:nn]),lty=c(0,1,1,1,1),
       col=color,pch=c(1,NA,NA,NA,NA))

}

