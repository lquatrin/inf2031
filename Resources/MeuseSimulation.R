# generate 5 conditional simulations
library(gstat)
library(sp)

number_of_simulations <- 10
name_of_prop <- "cadmium"

data(meuse)
coordinates(meuse) = ~x+y
v <- variogram(log(cadmium)~1, meuse)
m <- fit.variogram(v, vgm(1, "Sph", 300, 1))
plot(v, model = m)
set.seed(131)
data(meuse.grid)
gridded(meuse.grid) = ~x+y
sim <- krige(formula = log(cadmium)~1, meuse, meuse.grid, model = m, 
             nmax = 15, beta = 5.9, nsim = number_of_simulations)
# show all 5 simulation
spplot(sim, col.regions = colorRampPalette(c("blue","light blue","light green","green","yellow", "orange", "red")))

x_coords <- c(1:length(sim))
y_coords <- c(1:length(sim))
xyvalues <- rep(1.0, times = length(sim))

for (ith in c(1:number_of_simulations))
{
  ith_sim <- paste(c("sim",ith), collapse = "")
  
  for (coordinate in c(1:length(sim[ith_sim]))){
    # resolution: 2-40
    
    # X: Min - 178440 | Max - 181560 (-20 to anchor on left)
    x_coords[coordinate] = (as.numeric(meuse.grid$x[coordinate]) - 178440 - 20) / 40.0
    
    # Y: Min - 329600 | Max - 333760 (-20 to anchor on bottom)
    y_coords[coordinate] = (as.numeric(meuse.grid$y[coordinate]) - 329600 - 20) / 40.0
    
    xyvalues[coordinate] = as.numeric(sim[[ith_sim]][coordinate])
  }
  
  meuse_data <- data.frame(X = x_coords,
                           Y = y_coords,
                           V = xyvalues)
  
  write.table(meuse_data, paste(c("D:/GitHub/",name_of_prop,"/",name_of_prop,"_",ith,".prop"), collapse=""), sep="\t", row.names = FALSE, col.names = FALSE)
}