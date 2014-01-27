function postprocessing()
close all

pre = 'lamboV2';

grid=load (strcat(pre,'grid.txt'));
v=load (strcat(pre,'v.txt'));
u=load (strcat(pre,'u.txt'));

dyu = diff(u,1,2); % 1st order dy
dxv = diff(v,1,1); % 1st order dx
w = dxv(1:end,1:end-1) - dyu(1:end-1,1:end) ;

[NyPlus1,NxPlus1] = size(grid);
Ny = NyPlus1-1;
Nx = NxPlus1-1;

Nlines = 100;

startx = [ones(1,Nlines),linspace(1,Nx+1,Nlines)];
starty = [linspace(1,Ny,Nlines)';(Ny)*ones(Nlines,1)];

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
 streamline(u,v,startx,starty,[0.2]);
% 
 
end
