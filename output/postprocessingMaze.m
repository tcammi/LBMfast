function postprocessingMaze()
close all

pre = 'maze';

grid=load (strcat(pre,'grid.txt'));
v=load (strcat(pre,'v.txt'));
u=load (strcat(pre,'u.txt'));
v = -v;
u = -u;
dyu = diff(u,1,2); % 1st order dy
dxv = diff(v,1,1); % 1st order dx
w = dxv(1:end,1:end-1) - dyu(1:end-1,1:end) ;

[NyPlus1,NxPlus1] = size(grid);
Ny = NyPlus1-1;
Nx = NxPlus1-1;

Nlines = 1000;

startx = [(Nx-200)*ones(1,Nlines)];
starty = [linspace(200,350,Nlines)];
imagesc(grid)
size(grid)

hold off
imagesc(w)
hold on

N = sum(sum(grid==0));
ii = zeros(N,1);
jj = zeros(N,1);
counter = 1;
for i=1:Ny+1
    for j=1:Nx+1
        
        if (grid(i,j) == 0 || grid(i,j) ==-1)
            ii(counter,1)=i;
            jj(counter,1)=j;
            counter = counter+1;
        end
    end
end



plot(jj,ii,'.k');

 hold on
%quiver(u,v);
 streamline(u,v,startx,starty,[0.1 10000000]);
% 
 
end
